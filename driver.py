import os, sys
from datetime import date

today=str(date.today())
version ='1'

#This python script is used to run the main C script from outside the root environment.
#This makes plots for all histograms.

histdict={
    '3L_onZ_HTlep':{'channel':'3L_onZ', 'plot':'HTlep', 'name':'HTlep (3L, onZ)'},
}

for hist, value in histdict.items():
    channelname = value['channel']
    plotname = value['plot']
    plottitle = value['name']

    #Managing the output:
    ofname = channelname+'_'+plotname+'_'+today+'_version'+version+'.png'
    outdir = 'outputs/'+today+'_version'+version+'/'
    make_outdir = 'mkdir -p '+outdir
    os.system(make_outdir)
    ofname = outdir+ofname #This is the full path to the output png file
    
    #Calling ROOT and executing the C script:
    arguments=f'"{channelname}", "{plotname}", "{plottitle}","{ofname}"'
    processline = f"root -l -b -q 'make_overlay.C({arguments})'"
    #print(processline)
    os.system(processline)

print(f'\nAll plots are dumped in the following folder : {outdir}')
    
