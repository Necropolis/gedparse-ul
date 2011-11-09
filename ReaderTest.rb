# Reader test

require './GedcomReader'
require 'choice'
require 'mongo'
require 'pp'
require 'paint'

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
while !recs.empty?
  print "Inserting records... "
  subrecs = recs.take 50
  col.insert(subrecs)
  print "#{Paint["%07d" % recs.length, :green]} remaining\n"
end
