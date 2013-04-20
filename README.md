## Installation directions

### Qt SDK + zipped source of SPOT

1. Download the Qt SDK for your platform [here](http://qt-project.org/downloads
   "Download Qt")

2. Run the file you downloaded to install the Qt SDK.

3. Download the .zip file for SPOT
   [here](https://github.com/hazelnusse/SPOT/zipball/master "SPOT source code
   zipped")

4. Unzip the .zip file into a folder

5. Open Qt Creator (installed in step 2), select File->Open File or Project and
   choose `SPOT.pro`

6. Click the Green triangle button on the lower left to build and run SPOT.

## Python Script

Once you have run SPOT, you will end up with two files:
`<filename>_interactions.txt` and `<filename>_notes.txt`, which contain time
stamped coded interactions and notes, respectively.  To generate plots from the
interaction data, run the Python script in the scripts directory as follows:

  $ cd scripts
  $ ./makeplots <file>

Where you should replace <file> with the name (and path, if not in the scripts
directory) with the filename you chose to save your data in.  For example, to
run the script on the data in the observations directory, you would do:

  $ cd scripts
  $ ./makeplots ../observations/CLH_050212_interactions.txt

