#!/usr/env ruby

require 'mongo'
require 'pp'
require 'paint'
require 'highline'

def pause
  case STDIN.getc
  when 'x'
    exit
  end
end

db = Mongo::Connection.new.db('scots')
col = db['records_low']

name_regex=/[\w\.\'\(\)\- ]+/
place_regex=/^(?<countycode>#{name_regex}),\s+(?<country>#{name_regex}),\s+(?<county>#{name_regex}),\s+(?<town>#{name_regex})\s?$/
ext_place_regex=/^(?<countycode>#{name_regex}),\s+(?<country>#{name_regex}),\s+(?<county>#{name_regex}),\s+(?<borough>#{name_regex}),\s+(?<city>#{name_regex})\s?$/

query={
  "$or" => [
    {
      "type" => "FAM",
      "marriage.place" => {
        "$exists" => true
      }
    },
    {
      "type" => "INDI",
      "event.place" => {
        "$exists" => true
      }
    }
  ]
}

col.find(query, :snapshot => true).each do |record|

  place = nil
  case record["type"]
  when "FAM"
    place = record["marriage"]["place"]
  when "INDI"
    place = record["event"]["place"]
  else
    puts "Unknown record type"
    pp record
    pause
  end
  
  parsed_place=Hash.new
  rgx=nil
  if rgx=place.match(place_regex)
    puts "[[ #{Paint["REGEX MATCH", :green]} ]]     PLACE #{place}"
    parsed_place[:countycode]=rgx[:countycode]
    parsed_place[:country]=rgx[:country]
    parsed_place[:county]=rgx[:county]
    parsed_place[:town]=rgx[:town]
  elsif rgx=place.match(ext_place_regex)
    puts "[[ #{Paint["REGEX MATCH", :green]} ]] EXT_PLACE #{place}"
    parsed_place[:countycode]=rgx[:countycode]
    parsed_place[:country]=rgx[:country]
    parsed_place[:county]=rgx[:county]
    parsed_place[:city]=rgx[:city]
    parsed_place[:borough]=rgx[:borough]
  else
    puts "[[ #{Paint["REGEX  FAIL", :red, :blink]} ]]           #{place}"
    pause
  end
  
  case record["type"]
  when "FAM"
    col.update({"_id"=>record["_id"]}, {"$set"=>{"marriage.place"=>parsed_place}})
    puts "                            [[ #{Paint["UPDATED", :green]} ]] #{parsed_place}"
  when "INDI"
    col.update({"_id"=>record["_id"]}, {"$set"=>{"event.place"=>parsed_place}})
    puts "                            [[ #{Paint["UPDATED", :green]} ]] #{parsed_place}"
  else
    puts "Unknown record type"
    pp record
    pause
  end
  
end
