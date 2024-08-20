import math
import sys
import os
import getpass
from os import environ
from ROOT import TFile, TObjString

class pars:
    MYDIR = '/w/halld-scshelf2101/halld3/home/ihossain/ti_dn_10KHz_32_pixel_out'
    inputThetaList = 'theta_values.list'
    macrosTopDir = '/w/halld-scshelf2101/halld3/home/ihossain/eicdirc/build'
    nEventsPerJob = 50000
    nTotalEvents = 1250000
    trackingResolutionMapDir = '/w/halld-scshelf2101/halld3/home/ihossain/eicdirc/data'

nArgs = len(sys.argv)
if nArgs != 1:
    print("Usage: python3 sim_job_submit.py")
    sys.exit()

def makeSLURMJob():
    print("Creating SLURM submission files")

    infile = open(pars.inputThetaList, "r")
    line = infile.readline()
    slurmDir = os.path.join(pars.MYDIR, 'slurmJobs')
    os.makedirs(slurmDir, exist_ok=True)
    submitScriptName = os.path.join(slurmDir, 'submitJobs.sh')
    submitScript = open(submitScriptName, "w")
    os.chmod(submitScriptName, 0o744)
    submitScript.write("#!/bin/bash\n")

    outputPath = os.path.join(pars.MYDIR, 'hits_root_files')
    outputLogPath = os.path.join(pars.MYDIR, 'log')
    os.makedirs(outputPath, exist_ok=True)
    os.makedirs(outputLogPath, exist_ok=True)

    if not pars.macrosTopDir.startswith('/'):
        pars.macrosTopDir = os.path.join(os.getcwd(), pars.macrosTopDir)

    print()
    print("Input directory: {}".format(pars.macrosTopDir))
    print(" Input theta list: {}".format(pars.inputThetaList))
    print("Output directory: {}".format(outputPath))
    print("   Log directory: {}".format(outputLogPath))
    print()

    nJobs = 0
    while line:
        inputTheta = line.replace("\n", "")

        nEvents = nJobs * pars.nEventsPerJob
        if (pars.nTotalEvents > 0) and (nEvents >= pars.nTotalEvents):
            break

        fileTag = "{0}_deg_mix_pik_{1}_events".format(inputTheta, pars.nEventsPerJob)
        slurmOutputInfo = "{0}/slurm-{1}".format(outputLogPath, fileTag)
        outputFile = outputPath + "/hits_{}.root ".format(fileTag)

        sim_command = "cd {0} && ./eicdirc -o ".format(pars.macrosTopDir) + outputFile + "-r 0 -theta {0} -x \"mix_pik\" -p 6.0 -w 0 -g 1 -dn 116640000 -c 4 -l 3 -trackingres 0.0005 -v 0 -gz 1 -ev 0 -b 1 -e {1}".format(inputTheta, pars.nEventsPerJob)

        env_command_1 = "source /cvmfs/oasis.opensciencegrid.org/jlab/hallb/clas12/sw/setup.csh"
        env_command_2 = "source /cvmfs/oasis.opensciencegrid.org/jlab/geant4/ceInstall/geant4_cvmfs.csh"
       
        slurmFileName = "slurmJob_{}.job".format(fileTag)
        slurmFile = open("{0}/{1}".format(slurmDir, slurmFileName), "w")
        slurmFile.write("#!/bin/bash\n")
        slurmFile.write("#\n")
        slurmFile.write("#SBATCH --account=halld\n")
        slurmFile.write("#SBATCH --nodes=1\n")
        slurmFile.write("#SBATCH --ntasks=1\n")
        slurmFile.write("#SBATCH --mem-per-cpu=4000\n")
        slurmFile.write("#SBATCH --job-name=slurm-{0}\n".format(fileTag))
        slurmFile.write("#SBATCH --time=8:00:00\n")
        slurmFile.write("#SBATCH --gres=disk:2000\n")
        slurmFile.write("#SBATCH --constraint=el9\n")  # Change to el7&farm19 if needed
        slurmFile.write("#SBATCH --output=" + slurmOutputInfo + ".out\n")
        slurmFile.write("#SBATCH --error=" + slurmOutputInfo + ".err\n")
        slurmFile.write("# Check and change to the user scratch directory if it exists\n")
        slurmFile.write("if [ -d /scratch/" + getpass.getuser() + " ]; then\n") 
        slurmFile.write("    cd /scratch/" + getpass.getuser() + "\n")
        slurmFile.write("else\n")
        slurmFile.write("    cd /tmp\n")
        slurmFile.write("fi\n")
        slurmFile.write("#\n")
        slurmFile.write("\n")
        slurmFile.write("printf \"Start time: \"; /bin/date\n")
        slurmFile.write("printf \"host: \"; /bin/hostname -A\n")
        slurmFile.write("printf \"user: \"; /usr/bin/id\n")
        slurmFile.write("printf \"cwd: \"; /bin/pwd\n")
        slurmFile.write("echo \n")
        slurmFile.write("echo \"----------------------------------------------\"\n")
        slurmFile.write("echo \n")
        slurmFile.write("\n")
        slurmFile.write("# Create and cd to dedicated working directory\n")
        slurmFile.write("mkdir -p workdir_${SLURM_JOB_ID}\n")
        slurmFile.write("cd workdir_${SLURM_JOB_ID}\n")
        slurmFile.write("printf \"cwd: \"; /bin/pwd\n")
        slurmFile.write("\n")
        slurmFile.write(sim_command + "\n")
        slurmFile.write("\n")
        slurmFile.write("echo \n")
        slurmFile.write("echo \"----------------------------------------------\"\n")
        slurmFile.write("rm -rf workdir_${SLURM_JOB_ID}\n")
        slurmFile.write("printf \"End time: \"; /bin/date\n")
        slurmFile.close()

        submitScript.write("sbatch {}\n".format(os.path.join(slurmDir, slurmFileName)))

        nJobs += 1
        if (pars.nTotalEvents > 0) and (nEvents >= pars.nTotalEvents):
            submitScript.close()
            break
        line = infile.readline()

    print("\nSLURM submission files have been written to:\n{}".format(slurmDir))
    print("\nThis setup will submit {} jobs".format(nJobs))
    print("\nYou can submit your jobs with the script:\n{}".format(submitScriptName))

makeSLURMJob()