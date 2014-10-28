Pod::Spec.new do |s|
  s.name         = "PolarSSL"
  s.version      = "0.0.1"
  s.summary      = "PolarSSL"

  s.description  = <<-DESC
		Polar SSL library
                  DESC

  s.homepage     = "https://polarssl.org/"
  s.license      = { :type => "GPL", :file => "LICENSE" }
  s.author       = { "Jonathan Dalrymple" => "jonathan@float-right.co.uk" }

  # s.platform     = :ios
  # s.platform     = :ios, "5.0"

  #  When using multiple platforms
  # s.ios.deployment_target = "5.0"
  # s.osx.deployment_target = "10.7"

  s.source       = { :git => "git@github.com:veritech/polarssl.git", :tag => "polarssl-1.3.9" }
  
  s.source_files  = "include/polarssl/*.h"
  s.preserve_paths = "library/libpolarssl.a"
  s.vendored_library = "libpolarssl.a"

  #This builds the project
  s.prepare_command = <<-CMD
    make lib
  CMD

  s.libraries = "polarssl"
 
  s.xcconfig = { "LIBRARY_SEARCH_PATHS" => "$(PODS_ROOT)/PolarSSL/library" }

end
