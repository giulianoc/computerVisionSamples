
# Copyright (C) Giuliano Catrambone (giuliano.catrambone@catrasoftware.it)

# This program is free software; you can redistribute it and/or 
# modify it under the terms of the GNU General Public License 
# as published by the Free Software Foundation; either 
# version 2 of the License, or (at your option) any later 
# version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

# Commercial use other than under the terms of the GNU General Public
# License is allowed only after express negotiation of conditions
# with the authors.

cmake_minimum_required(
	VERSION 3.1
)

project(
	ComputerVisionSamples
)

SET(CMAKE_CXX_FLAGS "-std=c++14")


set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE RelWithDebInfo)
#set(CMAKE_BUILD_TYPE Release)

set(COMPUTERVISION_VERSION_MAJOR 1)
set(COMPUTERVISION_VERSION_MINOR 0)

add_subdirectory(01_displayPicture/src)
add_subdirectory(02_videoPlayer/src)
add_subdirectory(03_smoothingPicture/src)
add_subdirectory(04_pyrUpAndDown/src)
add_subdirectory(05_cannyPicture/src)
add_subdirectory(06_writeAVIFile/src)
add_subdirectory(07_faceRecognition/src)

