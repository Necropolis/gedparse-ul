# Reader test

require './GedcomReader'
require 'choice'
require 'mongo'
require 'pp'
require 'paint'

def pause
  case STDIN.getc
  when 'x'
    exit
  end
end

Choice.options do
  
  header 'GEDCOM Parser Options'
  
  option :file, :required => true do
    short '-f'
    long '--file=FILE'
    desc 'The file to parse'
  end
  
end

f=File.absolute_path Choice.choices[:file]
r=FamilySearch::GEDCOM::Reader.new(f, true)
db = Mongo::Connection.new.db('scots')
col = db['records_low']

r.parse!

puts "Inserting records!"
recs = r.records
r=nil
take_amount = 5573
while !recs.empty?
  print "Inserting records... "
  subrecs = recs.take take_amount
  pp subrecs
  pause
  # col.insert(subrecs)
  recs = recs.drop take_amount
  print "#{Paint["%07d" % recs.length, :green]} remaining from #{Paint[f, :green]}\n"
end
