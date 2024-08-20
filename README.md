IFarm Job Submission Guide
Overview

This repository provides scripts and instructions for running simulation and reconstruction jobs both on the JLab IFarm and on your local PC.
Running on JLab IFarm

If you are running jobs on JLab IFarm, you do not need to install any additional software on your PC. Instead, ensure you have properly sourced the environment. Follow the installation instructions for eicdirc (https://github.com/rdom/eicdirc).

Running Locally
If you wish to run the code on your local PC, you need to install the following software:

    Geant4
    Qt
    ROOT

Job Submission Instructions
For Geometric Reconstruction
1. Create Required Directories

bash

mkdir Job_submit_sim
mkdir Job_submit_out
mkdir Job_submit_reco

    Job_submit_sim: Directory for scripts.
    Job_submit_out: Directory for simulation output.
    Job_submit_reco: Directory for reconstruction output.

2. Submit Simulation Job

    Navigate to the simulation directory:

    bash

cd Job_submit_sim

Edit the sim_new_job_submit.py script to fit your requirements. The simulation command is included in the script. For additional details, follow (https://github.com/rdom/eicdirc).

Submit the job:

bash

    python3 sim_new_job_submit.py

    The simulation output will be located in the Job_submit_out directory.

3. Submit Reconstruction Job

    Navigate to the simulation directory:

    bash

cd Job_submit_sim

Edit the geo_reco_edited_job_submit.py script to meet your needs. The reconstruction command is included in the script. For additional details,(https://github.com/rdom/eicdirc).

Submit the job:

bash

    python3 geo_reco_edited_job_submit.py

    The reconstruction output will be located in the Job_submit_reco directory.

4. Analyze Results

After obtaining the reconstruction results, you can create performance plots such as photon yield, single photon resolution, and separation power using the following scripts:

    nph_geo_comparison_reco.C
    sep_gr_geo_comparison_reco.C
    Spr_geo_edited_comparison_all_reco.C

For Time Imaging Reconstruction
1. Create Required Directories

bash

mkdir ti_Job_submit_sim
mkdir ti_Job_submit_out
mkdir ti_Job_submit_reco

    ti_Job_submit_sim: Directory for scripts.
    ti_Job_submit_out: Directory for simulation output.
    ti_Job_submit_reco: Directory for reconstruction output.

2. Submit Simulation Job

    Navigate to the simulation directory:

    bash

cd ti_Job_submit_sim

Edit the ti_sim_new_job_submit.py script to fit your requirements. The simulation command is included in the script. For additional details, follow (https://github.com/rdom/eicdirc).

Submit the job:

bash

    python3 ti_sim_new_job_submit.py

    The simulation output will be located in the ti_Job_submit_out directory.

3. Submit Reconstruction Job

    Navigate to the simulation directory:

    bash

cd ti_Job_submit_sim

Edit the ti_geo_job_submit.py script to meet your needs. The reconstruction command is included in the script. For additional details, (https://github.com/rdom/eicdirc).

Submit the job:

bash

    python3 ti_geo_job_submit.py

    The reconstruction output will be located in the ti_Job_submit_reco directory.

4. Analyze Results

After obtaining the reconstruction results, you can create performance plots such as photon yield and separation power using the following scripts:

    nph_new_ti_geo_reco.C
    sep_new_ti_geo_reco.C

Additional Information

    Ensure you have the necessary permissions and environment settings before running these jobs on IFarm.
