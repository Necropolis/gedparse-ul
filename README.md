# Misc. GEDCOM Code

This mess was all written to facilitate the conversion of some old unlinked GEDCOM files to a MongoDB instance, from where they were sanitized and exported into a CSV. From there another team used another piece of software to convert that to a linked GEDCOM.

This code is very specialized and wasn't intended for heavy re-use without modification.

## GedcomReader.rb

This is a class, `FamilySearch::GEDCOM::Reader`, which is built to parse unlinked GEDCOM files and generate an array of records. Each record is a hash. An example record would be:

	{:type=>"FAM",
	  :sex=>"MS",
	  :spouse=>{:standardised_surname=>"MARTIN", :name=>"/MARTEIN"},
	  :marriage=>
	   {:date=>{:day=>"26", :month=>"Feb", :year=>"1587"},
	    :place=>"Fife, Scotland, Fife, Anstruther Wester"},
	  :misc=>"FR106",
	  :batch=>"M114032"}