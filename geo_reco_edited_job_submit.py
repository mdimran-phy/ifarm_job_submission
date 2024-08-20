import math
import sys
import os
import getpass
from ROOT import TFile, TObjString

class Pars:
    MYDIR = '/w/halld-scshelf2101/halld3/home/ihossain/gr_dn_HRPPD_3.3_pixel_10KHz_reco_tc_0.02ns'
    inputThetaList = 'Theta_values.list'
    macrosTopDir = '/w/halld-scshelf2101/halld3/home/ihossain/gr_dn_HRPPD_3.3_pixel_10KHz_out/hits_root_files'
    dircmacrosTopDir = '/w/halld-scshelf2101/halld3/home/ihossain/eicdirc/build'
    nEventsPerJob = 4000
    nTotalEvents = 100000
    trackingResolutionMapDir = '/w/halld-scshelf2101/halld3/home/ihossain/eicdirc/data'

nArgs = len(sys.argv)
if nArgs != 1:
    print("Usage: python3 geo_reco_edited_job_submit.py")
    sys.exit()

def makeSLURMJob():
    print("Creating SLURM submission files")

    infile = open(Pars.inputThetaList, "r")
    line = infile.readline()
    slurmDir = os.path.join(Pars.MYDIR, 'geo_reco_slurmJobs')
    os.makedirs(slurmDir, exist_ok=True)
    submitScriptName = os.path.join(slurmDir, 'submitJobs.sh')
    submitScript = open(submitScriptName, "w")
    os.chmod(submitScriptName, 0o744)
    submitScript.write("#!/bin/bash\n")

    outputPath = os.path.join(Pars.MYDIR, 'output_files')
    outputLogPath = os.path.join(Pars.MYDIR, 'output_log')
    os.makedirs(outputPath, exist_ok=True)
    os.makedirs(outputLogPath, exist_ok=True)

    if not Pars.macrosTopDir.startswith('/'):
        Pars.macrosTopDir = os.path.join(os.getcwd(), Pars.macrosTopDir)

    print()
    print("Input directory: {}".format(Pars.macrosTopDir))
    print(" Input theta list: {}".format(Pars.inputThetaList))
    print("Output directory: {}".format(outputPath))
    print("   Log directory: {}".format(outputLogPath))
    print()

    nJobs = 0
    while line:
        inputTheta = line.strip()

        nEvents = nJobs * Pars.nEventsPerJob
        if (Pars.nTotalEvents > 0) and (nEvents >= Pars.nTotalEvents):
            break

        inputfile = f"{Pars.macrosTopDir}/hits_{inputTheta}_deg_mix_pik_{Pars.nEventsPerJob}_events.root"
        lutfile = "/w/halld-scshelf2101/halld3/home/ihossain/eicdirc/build/data/lut_HRPPD_3.3_pixel_new.avr.root"
        fileTag = f"{inputTheta}_deg"

        slurmOutputInfo = f"{outputLogPath}/slurm-{fileTag}"
        initialoutputFile = f"output_{fileTag}.root"
        outputFile = f"{outputPath}/output_{fileTag}.root"

        reco_command = (
            f"cd {Pars.dircmacrosTopDir} && ./eicdirc -i {inputfile} -u {lutfile} -o {initialoutputFile} "
            "-r 2 -timecut 0.02 -v 2 -e 0 -trackingres 0.0005"
        )
        env_command_1 = "source /cvmfs/oasis.opensciencegrid.org/jlab/hallb/clas12/sw/setup.csh"
        env_command_2 = "source /cvmfs/oasis.opensciencegrid.org/jlab/geant4/ceInstall/geant4_cvmfs.csh"
        #env_command = "source /u/home/ihossain/setup_new.csh" 

        slurmFileName = f"slurmJob_{fileTag}.job"
        slurmFile = open(os.path.join(slurmDir, slurmFileName), "w")
        slurmFile.write("#!/bin/csh\n")  # Changed to csh shell
        slurmFile.write("#SBATCH --account=halld\n")
        slurmFile.write("#SBATCH --nodes=1\n")
        slurmFile.write("#SBATCH --ntasks=1\n")
        slurmFile.write("#SBATCH --mem-per-cpu=2000\n")
        slurmFile.write(f"#SBATCH --job-name=slurm-{fileTag}\n")
        slurmFile.write("#SBATCH --time=0:20:00\n")
        slurmFile.write("#SBATCH --gres=disk:2000\n")
        slurmFile.write(f"#SBATCH --output={slurmOutputInfo}.out\n")
        slurmFile.write(f"#SBATCH --error={slurmOutputInfo}.err\n")
        slurmFile.write(f"#SBATCH --chdir=/scratch/{getpass.getuser()}\n")
        slurmFile.write("\n")
        slurmFile.write("printf \"Start time: \"; /bin/date\n")
        slurmFile.write("printf \"host: \"; /bin/hostname -A\n")
        slurmFile.write("printf \"user: \"; /usr/bin/id\n")
        slurmFile.write("printf \"cwd: \"; /bin/pwd\n")
        slurmFile.write("echo \n")
        slurmFile.write("echo \"----------------------------------------------\"\n")
        slurmFile.write("echo \n")
        slurmFile.write("# Create and cd to dedicated working directory\n")
        slurmFile.write("mkdir -p workdir_${SLURM_JOBID}\n")
        slurmFile.write("cd workdir_${SLURM_JOBID}\n")
        slurmFile.write("printf \"cwd: \"; /bin/pwd\n")
        slurmFile.write("\n")
        slurmFile.write(env_command_1 + "\n")
        slurmFile.write(env_command_2 + "\n")
        slurmFile.write(reco_command + "\n")
        slurmFile.write(f"mv {initialoutputFile} {outputFile}\n")
        slurmFile.write("echo \n")
        slurmFile.write("echo \"----------------------------------------------\"\n")
        slurmFile.write("rm -rf workdir_${SLURM_JOBID}\n")
        slurmFile.write("printf \"End time: \"; /bin/date\n")
        slurmFile.close()

        submitScript.write(f"sbatch {os.path.join(slurmDir, slurmFileName)}\n")

        nJobs += 1
        line = infile.readline()

    submitScript.close()
    infile.close()

    print("\nSLURM submission files have been written to:\n{}".format(slurmDir))
    print("\nThis setup will submit {} jobs".format(nJobs))
    print("\nYou can submit your jobs with the script:\n{}".format(submitScriptName))

makeSLURMJob()
