# Reads an GEDCOM

require 'strscan'
require 'ripl'

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
      
      attr_accessor :records
      
      def initialize(fname)
        @fname = File.absolute_path fname
        @records = Array.new
        
        name_regex=/[\w\.\'\(\)\- ]+/
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
          },
          :place => {
            :place => /^(?<countycode>#{name_regex}),\s+(?<country>#{name_regex}),\s+(?<county>#{name_regex}),\s+(?<town>#{name_regex})\s?$/,
            :ext_place => /^(?<countycode>#{name_regex}),\s+(?<country>#{name_regex}),\s+(?<county>#{name_regex}),\s+(?<borough>#{name_regex}),\s+(?<city>#{name_regex})\s?$/
          }
        }
        
      end
      
      def self.parse fname
        parser = FamilySearch::GEDCOM::Reader.new fname
        parser.parse do |filename, record, records_read|
          yield filename, record, records_read
        end
      end
      
      # block callback of filename, record, records_read
      def parse
        recs=0
        scanner = StringScanner.new(File.open(@fname, File::RDONLY).read)
        scanner.scan_until(/^0/)
        while !scanner.eos?
          begin
            record = Hash.new
            scanner.forward 1
            record[:type] = scanner.scan(/\w+/)
            record.merge! parse_helper(scanner, 1)
            record = coalesce_record(record)
          rescue
          end
          unless record[:type].match /FAM|INDI/
            puts "aak!"
            Ripl.start :binding => binding
          end
          recs=recs+1
          yield @fname, record, recs
        end
      end
      
      # block callback of filename, record, records_read
      def parse!
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
          end
          yield @fname, record, @records.length
        end
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
            place = scanner.scan_until(/\r/).strip!
            parsed_place=Hash.new
            rgx=nil
            if rgx=place.match(@r[:place][:place])
              parsed_place[:countycode]=rgx[:countycode]
              parsed_place[:country]=rgx[:country]
              parsed_place[:county]=rgx[:county]
              parsed_place[:town]=rgx[:town]
            elsif rgx=place.match(@r[:place][:ext_place])
              parsed_place[:countycode]=rgx[:countycode]
              parsed_place[:country]=rgx[:country]
              parsed_place[:county]=rgx[:county]
              parsed_place[:city]=rgx[:city]
              parsed_place[:borough]=rgx[:borough]
            else
              raise "Unknown location format!"
            end
            record[:place] << parsed_place
          when /BATC/
            scanner.scan /\s+/
            record[:batch] << scanner.scan(/\w+/)
          when /MISC/
            scanner.scan /\s+/
            record[:misc] << scanner.scan_until(/\r/).strip!
          when /DATE/
            date = scanner.scan_until(/\r/).strip!
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
              raise "Unknown date format!"
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
            raise "Unknown type!"
          end
          
          l = scanner.scan_until /^[[:digit:]]/
          unless scanner.eos?
            scanner.back 1
            l.strip!
            if l.to_i > level
              raise "Recursion unexpected"
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
        when @r[:name][:last]
          parts[:last] = $1
        when @r[:name][:first]
          parts[:first] = $1
        else
          raise "Unknown name format!"
        end
        
        parts
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
      
    end
  end
end
