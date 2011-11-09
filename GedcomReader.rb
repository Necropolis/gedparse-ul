# Reads an GEDCOM

require 'ripl'
require 'strscan'
require 'pp'

class StringScanner
  def back(num)
    self.pos = self.pos - num
  end
  def forward(num)
    self.pos = self.pos + num
  end
end

module FamilySearch
  module GEDCOM
    class Reader
      
      # The file the GEDCOM is being read from
      attr_accessor :fname
      # Whether or not to print out stuff to the screen
      attr_accessor :log
      
      attr_accessor :records
      
      def initialize(fname,log=false)
        @fname = File.absolute_path fname
        @log = log
        @records = Array.new
        
        @r = {
          :date => {
            :year_only => /^[[:digit:]]{4}$/,
            :month_year => /^([[:alpha:]]+)\s+([[:digit:]]{4})$/,
            :day_year => /^([[:digit:]]{1,2})\s+([[:digit:]]{4})$/,
            :day_month => /^([[:digit:]]{1,2})\s+([[:alpha:]]+)$/,
            :day_month_year => /^([[:digit:]]{1,2})\s+(\w+)\s+([[:digit:]]{4})$/
          },
          :name => {
            :first_last => /^(.+)\s+\/(.+)$/,
            :first => /^([\w\. \-\'^\/]+)$/,
            :last => /\s?\/(.+)$/
          }
        }
        
=begin
name.first needs to match:
  Thomas
  Mgret.
  ... Laird Of Bulthyle
  Helen Margaret-Eeena
=end
        
        @highline ||= begin
          require 'highline'
          HighLine.new
        end
        
      end
      
      def parse!
        require 'paint' if @log
        self.log "Parsing GEDCOM #{Paint[@fname, :red, :bright]}"
        puts @fname
        scanner = StringScanner.new(File.open(@fname, File::RDONLY).read)
        scanner.scan_until(/^0/)
        while !scanner.eos?
          begin
            record = Hash.new
            scanner.forward 1
            record[:type] = scanner.scan(/\w+/)
            record.merge! parse_helper(scanner, 1)
            @records << coalesce_record(record)
          rescue
            puts "#{Paint["Fatal Error #{$!}", :red, :yellow, :blink]}"
            br scanner
          end
          puts "#{Paint['Now serving', :green]} #{Paint["%07d" % @records.length, :yellow]} #{Paint['records in', :green]} #{Paint[@fname, :yellow]}" if @records.length % 7 == 0
          
        end
        self.log "Finished parsing GEDCOM #{Paint[@fname, :red, :bright]}"
      end
      
      def parse_helper(scanner, level=0)
        scanner.scan_until /^[[:digit:]]/
        scanner.back 1
        func = lambda {|hash,key| hash[key]=Array.new}
        record = Hash.new &func
        while scanner.scan(/\w+/).to_i == level
          scanner.scan /\s+/ # kill prefix whitespace
          type = scanner.scan /\w+/
          case type
          when /SEX/
            scanner.scan /\s+/
            record[:sex] << scanner.scan(/\w+/)
          when /MARR/
            record[:marriage] << parse_helper(scanner, level+1)
            scanner.back 1
            next
          when /SPOU/
            spouse_name = name_parts scanner.scan_until(/\r/).strip!, scanner
            if scanner.peek(2).strip!.to_i > level
              spouse_detail = parse_helper(scanner, level+1)
              scanner.back 1
              spouse_detail[:name] << spouse_name
              record[:spouse] << spouse_detail
              next
            else
              r = Hash.new
              r[:name] = spouse_name
              record[:spouse] << r
            end
          when /PLAC/
            record[:place] << scanner.scan_until(/\r/).strip!
          when /BATC/
            scanner.scan /\s+/
            record[:batch] << scanner.scan(/\w+/)
          when /MISC/
            scanner.scan /\s+/
            record[:misc] << scanner.scan_until(/\r/).strip!
          when /DATE/
            date = scanner.scan_until(/\r/).strip!
            # puts date
            date_parsed = Hash.new
            case date
            when @r[:date][:year_only]
              date_parsed[:year] = date.to_i
            when @r[:date][:month_year]
              date_parsed[:month] = $1
              date_parsed[:year] = $2
            when @r[:date][:day_month]
              date_parsed[:day] = $1
              date_parsed[:month] = $2
            when @r[:date][:day_year]
              date_parsed[:day] = $1
              date_parsed[:year] = $2
            when @r[:date][:day_month_year]
              date_parsed[:day] = $1
              date_parsed[:month] = $2
              date_parsed[:year] = $3
            else
              puts "#{Paint["Unknown date format", :red, :yellow]} #{Paint[date, :yellow, :red]}"
              puts "[c]ontinue [ex]it [p]rompt [s]how"
              case @highline.ask('?> ') { |c| c.validate = /^[cexps]$/ }
              when 'c'
                return
              when 'e', 'x'
                exit
                return
              when 'p'
                Ripl.start :binding => binding
              when 's'
                scanner.back 190
                puts scanner.peek 190
                puts Paint["CURSOR", :red, :yellow, :blink]
                scanner.forward 190
                puts scanner.peek 190
                br scanner
              else
                puts 'Not an answer?'
              end
            end
            record[:date] << date_parsed
          when /NAME/
            name = scanner.scan_until(/\r/).strip!
            name = name_parts name, scanner
            if scanner.peek(2).strip!.to_i > level
              name_detail = parse_helper(scanner, level+1)
              scanner.back 1
              name_detail[:name] << name
              record[:name] << name_detail
              # record[:name] << 
              scanner.scan_until(/\r/).strip!
              next
            else
              n = Hash.new &func
              n[:name] << name
              record[:name] << n
            end
          when /STGN/
            scanner.scan(/\s+/)
            record[:standardised_given_name] << scanner.scan(/\w+/)
          when /STSN/
            scanner.scan /\s+/
            record[:standardised_surname] << scanner.scan(/\w+/)
          when /EVEN/
            type = scanner.scan_until(/\r/).strip!
            if scanner.peek(2).strip!.to_i > level
              event_detail = parse_helper(scanner, level+1)
              scanner.back 1
              event_detail[:type] << type
              record[:event] << event_detail
              next
            else
              n = Hash.new &func
              n[:type] << type
              record[:event] << n
            end
          when /MOTH/
            name = name_parts scanner.scan_until(/\r/).strip!, scanner
            if scanner.peek(2).strip!.to_i > level
              name_detail = parse_helper(scanner, level+1)
              scanner.back 1
              name_detail[:name] << name
              record[:mother] << name_detail
              scanner.scan_until(/\r/).strip!
              next
            else
              n = Hash.new &func
              n[:name] << name
              record[:mother] << n
            end
          when /FATH/
            name = name_parts scanner.scan_until(/\r/).strip!, scanner
            if scanner.peek(2).strip!.to_i > level
              name_detail = parse_helper(scanner, level+1)
              scanner.back 1
              name_detail[:name] << name
              record[:father] << name_detail
              scanner.scan_until(/\r/).strip!
              next
            else
              n = Hash.new &func
              n[:name] << name
              record[:father] << n
            end
          else
            puts "#{Paint["Unknown type", :red, :yellow]} #{Paint[type, :yellow, :red]}"
            br scanner
          end
          
          l = scanner.scan_until /^[[:digit:]]/
          unless scanner.eos?
            scanner.back 1
            l.strip!
            if l.to_i > level
              puts "#{Paint["Recursion Unexpected!", :yellow, :red]}"
              br scanner
            end
          end

        end
        
        record
      end
      
      def name_parts(name, scanner)
        parts = Hash.new
        case name
        when @r[:name][:first_last]
          parts[:first] = $1
          parts[:last] = $2
        when @r[:name][:first]
          parts[:first] = $1
        when @r[:name][:last]
          parts[:last] = $1
        else
          puts "name : '#{name}'"
          puts "[c]ontinue [ex]it [p]rompt [s]how"
          case @highline.ask('?> ') { |c| c.validate = /^[cexps]$/ }
          when 'c'
            return
          when 'e', 'x'
            exit
            return
          when 'p'
            Ripl.start :binding => binding
          when 's'
            show scanner
          else
            puts 'Not an answer?'
          end
        end
        name
      end
      
      def coalesce_record(r)
        if r.class == Hash
          r.each do |k,v|
            r[k] = coalesce_record v
          end
        elsif r.class == Array
          if r.length == 1
            r = coalesce_record r.last
          else
            r.map! do |e|
              coalesce_record e
            end
          end
        end
        r
      end
      
      def show(scanner)
        scanner.back 190
        puts scanner.peek 190
        puts Paint["CURSOR", :red, :yellow, :blink]
        scanner.forward 190
        puts scanner.peek 190
        br scanner
      end
      
      def br(scanner)
        puts "[c]ontinue [ex]it [p]rompt [s]how"
        case @highline.ask('?> ') { |c| c.validate = /^[cexps]$/ }
        when 'c'
          return
        when 'e', 'x'
          exit
          return
        when 'p'
          Ripl.start :binding => binding
        when 's'
          show scanner
        else
          puts 'Not an answer?'
        end
      end
            
      def log sz
        puts sz if @log
      end
      
    end
  end
end
