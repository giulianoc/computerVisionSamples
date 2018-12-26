
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

SET (SOURCES
	writeAVIFile.cpp
)

SET (HEADERS
)

include_directories ("/home/giuliano/catramms/opencv/include/opencv4")

link_directories ("/home/giuliano/catramms/opencv/lib")
link_directories ("/home/giuliano/catramms/ffmpeg-4.0.2/lib")

add_executable(writeAVIFile ${SOURCES} ${HEADERS})

target_link_libraries (writeAVIFile opencv_core)
target_link_libraries (writeAVIFile opencv_highgui)
target_link_libraries (writeAVIFile opencv_imgcodecs)
target_link_libraries (writeAVIFile opencv_imgproc)
target_link_libraries (writeAVIFile opencv_videoio)
target_link_libraries (writeAVIFile opencv_video)
target_link_libraries (writeAVIFile opencv_videostab)
target_link_libraries (writeAVIFile avcodec)



