SALIENCY DETECTION
==================

Work in progress.  

Derived from https://github.com/kkduncan/SaliencyDetection.git   The algorithm is the work of  "Relational Entropy-Based Saliency Detection in Images and Videos" by K. Duncan and S. Sarkar in the IEEE International Conference on Image Processing (2012).  This derivation is just cleaned up a little.

Changed:
- remove cruft
- remove git history
- use open CV for gradient

Future:
- explore acceleration openCV v3 transparent api to openCL?
- autotools to make a library
- gimp plugin


The .project is an Eclipse IDE project.  Requires JRE (Java runtime) and Eclipse C/C++ IDE.

There isn't a makefile yet, Eclipse generates one.

Depends on openCV v2 (package opencv-dev, which includes headers and libraries.)


