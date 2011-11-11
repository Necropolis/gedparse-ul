#!/usr/env ruby

require 'mongo'
require 'pp'
require 'paint'
require 'highline'
require 'csv'

db = Mongo::Connection.new.db('scots')
col = db['records_low']

csv_string = CSV.generate do |csv|
  col.find("type"=>"FAM").limit(10).each do |record|
    csv << record
  end
end

puts csv_string
