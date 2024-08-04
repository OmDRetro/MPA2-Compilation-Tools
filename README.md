# MPA2-Compilation-Tools
A set of tools to create album ROMs to load via Music Player Advance 2 by NEiM0D

# Prerequisites
 - Download the ffmpeg binaries
     - Option 1: Obtain the ffmpeg-release-essentials archive from [gyan.dev](https://www.gyan.dev/ffmpeg/builds/)
	     - Under release builds, look for `ffmpeg-release-essentials.7z` or `ffmpeg-release-essentials.zip`
	 - Option 2: Get the latest Github release from [here](https://github.com/BtbN/FFmpeg-Builds/releases)
	     - `ffmpeg-master-latest-win64-gpl.zip` should contain the standalone binaries
		     - _DO NOT DOWNLOAD THE SHARED VERSION!_

 - Download [Music Player Advance 2](https://web.archive.org/web/20181020204131/http://www.cellularmobilephones.com/gba_net/MusicPlayer_Advance_2.zip)
     - There's an executable binary in that archive called `MPAWRITE.EXE`. That application is needed for Step 2 of the `MPA2 Compilation Tools`

 - Download the latest [MPA2 Compilation Tools](https://github.com/OmDRetro/MPA2-Compilation-Tools/releases)
 
# How to use
 - Extract the `MPA2_Tools` from the `MPA2 Compilation Tools archive`.
 - Inside that folder you'll find 3 folders, namely:
     - `Step1-PCM_conversion`
	 - `Step2-MPA_conversion`
	 - `Step3-ROM_packing`
 - Starting with `Step1-PCM_conversion`:
     - Please extract the `ffmpeg.exe` binary from `ffmpeg-release-essentials` or `ffmpeg-master-latest-win64-gpl`
	 - Move the `ffmpeg.exe` binary to `MPA2_Tools\Step1-PCM_conversion\bin`
 - Next, with `Step2-MPA_conversion`:
     - Please extract the `MPAWRITE.exe` binary from `MusicPlayer_Advance_2.zip`
	 - Move the `MPAWRITE.exe` binary to `MPA2_Tools\Step2-MPA_conversion\`
	     - This is actually optional if you know what to do, but for the sake of this tutorial we'll place the application there.
 - Copy your music to `MPA2_Tools\Step1-PCM_conversion\Input\`
 - After copying your music, open the `Convert2PCM.bat` file
     - It will ask you for what kind of quality you want for each audio file
	 - Enter your choice then press enter.
	     - You'll have to repeat this step for each song
	 - Be sure to remember the bitrate as you'll need this later.
 - After converting all the audio files, you'll find the PCM conversions in:
     - `MPA2_Tools\Step1-PCM_conversion\Output\`
	     - Move all the PCM files to `MPA2_Tools\Step2-MPA_conversion`
 - Head over to the `Step2-MPA_conversion` directory
     - Open `MPAWRITE.exe`
	     - At the very bottom of the window, there's a `SECTION` called:
		     - "MusicPlayer Advance Encoder"
		 - For the `Raw 16-bit PCM file`, click `Browse` and navigate to `MPA2_Tools\Step2-MPA_conversion`
		     - Open the audio file you want to convert to MPA format.
         - For the `Save MPA file as`, click `Browse` and navigate to `MPA2_Tools\Step3-ROM_packing\Input`
		     - Type the name of the audio file or copy paste the audio's filename then hit `SAVE`
		 - For `Samplerate` this is the bitrate you used from `Convert2PCM.bat`.
		     - If you selected `1`,  set the `Samplerate` to `16000` from the dropdown
			 - If you selected `2`,  set the `Samplerate` to `11025` from the dropdown
			 - If you selected `3`,  set the `Samplerate` to `8000` from the dropdown
		 - As for `Channels`, typically audio tracks are `mono channel` so you can leave that as `mono`
		     - The only exception here is if the input audio file has stereo channels.
	     - Click / Hit `Encode`
		 - Repeat the steps for every PCM file you converted.
 - Lastly, head over to the `Step3-ROM_packing` directory.
     - Run or open the `Step3a-GenerateHeaders.bat` file.
	     - Wait until the prompt says "Step 3a is complete" or "Please execute Step 3b..."
		 - Close that prompt window.
	 - Next, run or open the `Step3b-GenerateMPAC.bat` file.
	     - Once the album compiler is done, you'll find the MPAC rom file in `MPA2_Tools\Step3-ROM_packing\Output\`
		 - Rename the `ALBUM.MPAC` to whatever you want, but do retain the file extension `*.MPAC`
	 - Transfer the `ALBUM` ROM to your microSD card.
 - Open the MPAC rom within SCFW and enjoy the beats 🎶
