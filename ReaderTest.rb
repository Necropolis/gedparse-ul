# Reader test

require './GedcomReader'
require 'choice'

require 'pp'

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
r.parse!
# pp r.records[0..20]
r=nil
