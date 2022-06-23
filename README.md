# WDFsPlugin

## Introduction

The aim of this project is to present a Virtual Analog modeling of the
famous Klon Centaur overdrive pedal, based on Wave Digital
Filters. In particular, we propose an analysis structured by a
stage decomposition of the overdrive, highlighting the WD tech-
niques utilized to model its complex topology (due to feedback
and feed-forward networks) and its characteristic non-linear
behaviour (due to the diodes in anti-parallel configuration). 
We mainly focused on a real-time transient simulation with the
purpose of realize a C++ plug-in version of the Centaur using
the JUCE platform

![alt text](https://github.com/Jacopo-brz/WDFsPlugin/tree/master/Images/klon_scheme.png)

## JUCE plugin Architecture
![alt text](https://github.com/Jacopo-brz/WDFsPlugin/tree/master/Images/klon_centaur_gui.png)


In order to implement our plug-in we used JUCE, a popular framework used by many
audio programmers for developing audio and graphic applications.
We compiled our code as a VST3 plugin, testing it in the Reaper
DAW with different audio tracks. The reader can immediately rec-
ognize in the figure the original Centaur design we decided to adopt
for our model’s gui.
The user can easily control the amount of distortion, the quantity of boost of the mid-gigh frequency and 
the output volume desired setting the value of the trhree potentiometers.
## How to use 


### Installing

* Clone ro download the repository
* Create a new basic-plugin in Projucer
* Copy the .cpp and .h files in the Source and build the project with your favourite IDE


### Executing program

Once you obtain the VST/VST3 file (follow the previous steps) you have simply to open it in a DAW assigning it to a MIDI or audio channel.


## Authors

Francesco Boarino

Jacopo Barzon



## References
* A. Fettweis, “Wave digital filters: Theory and practice,” Pro-
ceedings of the IEEE, vol. 74, no. 2, pp. 270–327, 1986.
* Proverbio, A. Bernardini, and A. Sarti, “Toward the wave
digital real-time emulation of audio circuits with multiple non-
linearities,” 10 2020.
* J. Zhang and J. O. S. III, “Real-time wave digital simulation
of cascaded vacuum tube amplifiers using modified blockwise
method,” Proceedings of the 21st International Conference on
Digital Audio Effects (DAFx-18), 9 2018.
* R. Giampiccolo, M. de Bari, A. Bernardini, and A. Sarti, “Wave
digital modeling and implementation of nonlinear audio cir-
cuits with nullors,” IEEE/ACM Transactions on Audio, Speech,
and Language Processing, vol. 29, pp. 3267–3279, 10 2021.
*  A. Bernardini, P. Maffezzoni, L. Daniel, and A. Sarti, “Wave-
based analysis of large nonlinear photovoltaic arrays,” IEEE
Transactions on Circuits and Systems I: Regular Papers,
vol. PP, pp. 1–14, 10 2017.
*  A. Bernardini, K. Werner, A. Sarti, and J. Smith, “Modeling
nonlinear wave digital elements using the lambert function,”
IEEE Transactions on Circuits and Systems I: Regular Papers,
vol. 63, pp. 1231–1242, 08 2016.
*  D. Albertini, A. Bernardini, and A. Sarti, “Antiderivative an-
tialiasing techniques in nonlinear wave digital structures,” Jour-
nal of the Audio Engineering Society, vol. 69, pp. 448–464, 11 2021.
*  https://www.electrosmash.com/klon-centaur-analysis
