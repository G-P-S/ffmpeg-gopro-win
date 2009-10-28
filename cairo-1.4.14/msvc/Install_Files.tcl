# $Header$

# Script for installing the decoder DLL files in the correct locations

# Get the input directory and target path
if {[llength $argv] < 2} {
	puts "Must specify the input directory and target path"
	exit 1
}

set InputDir [lindex $argv 0]
set TargetPath [lindex $argv 1]
set TargetDir [file dirname $TargetPath]

#puts "InputDir: [file nativename $InputDir]"
#puts "TargetPath: [file nativename $TargetPath]"
#puts "TargetDir: [file nativename $TargetDir]"



# Create the directory path if it does not already exist
proc CheckDirectory {pathname} {
	set pathname [file dirname $pathname]
	#puts "Checking directory path: $pathname"
	if {[file isdirectory $pathname] == 0} {
		puts "Creating directory path: $pathname"
		file mkdir $pathname
	}
}

# Install the file in the specified directory if it exists
proc SafeInstall {file folder} {
	set file [file normalize $file]
	set folder [file normalize $folder]
	
	if {[expr [file isdirectory $folder] == 0]} {
		# Create the directory
		puts "Creating directory $folder"
		file mkdir $folder
	}
	
	if {[file isdirectory $folder] == 0} {
		puts "Folder $folder is not a directory"
		exit 1
	}
	
	# Copy the file to the installation folder
	#puts "Copying [file nativename $file] to [file nativename $folder]"
	if {[catch {file copy -force $file $folder} result]} {
		puts "Error: Could not copy [file nativename $file] to [file nativename $folder]"
	} else {
		puts "Copied [file nativename $file] to [file nativename $folder]"
	}
}

# Install the decoder files in the correct locations
SafeInstall $TargetDir/libcairo14.lib ../
SafeInstall $TargetDir/libcairo14.dll ../
SafeInstall $TargetDir/libcairo14-64.lib ../
SafeInstall $TargetDir/libcairo14-64.dll ../
SafeInstall $TargetDir/libcairo14.dll "c:/Program Files (x86)/CineForm/Tools"
SafeInstall $TargetDir/libcairo14-64.dll "c:/Program Files (x86)/CineForm/Tools"

puts "Installation finished"

