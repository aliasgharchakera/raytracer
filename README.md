# Homework 5: Raytracer
# CS 440 Computer Graphics, Fall 2023
-----

# Purpose

This homework sets the foundation of an extendable ray tracing engine using principles of Object Oriented design. It implements some of the ray tracing topics we have covered, namely:

- casting and tracing a ray through a scene
- ray-primitive intersections
- shading primitives
- sampling a scene
- perspective and parallel projection
- anti-aliasing
- light sources
- acceleration structures

# Background

For this homework, you must be able to

- read and write object oriented code in C++
- compile a c++ project spanning multiple files in multiple directories
- understand raytacing in terms of vector arithmetic
- understand the concepts listed above

# The Problem Set

The problems as well as your tasks are defined in `hw5.tex` which is to be compiled using a LaTeX compiler.

# Submission

There are 2 parts to the submission.

## 5.1 Problem Set

Submit _all_ code files in the `raytracer` folder. `World.cpp` should `#include` the relevant file from the `build` folder corresponding to the high-res version of your showcase scene. Other `World::build` implementations (e.g. for the low-res version, or used to generate other pictures on your web page) should be included in the `build` folder. Compiling and running `raytracer.cpp` in the `raytracer` folder should generate the high-res image.

Include a `website` folder that includes your website, either as HTML, markdown, or a URL. The submitted web page must be complete, i.e. all the required assets are submitted and no links are broken.

This is a __team submission__, i.e. a single submission per team. Your team has a single repository to which each of you will have access. Your team submission will be assigned a __Submission Score__ based on the correctness of the contained solutions.

_Deadline_: 2359h on Monday, 18 December

# 5.2 Feedback

You will provide feedback on your team and on the assignment by filling the feedback form which will be made available as _HW 3.2_ on the course page. This is due at the same time as the problem solutions.

This is an __individual submission__, i.e. each of you has to fill the form. Doing so contributes to your __Team Factor__ which is 1 by default and is penalized in case of non-submission of the form, dishonest feedback, or unequal contribution to the submission as reported by your buddies and/or the commit history on GitHub.

_Deadline_: 2359h on Monday, 18 December

# Grading

Your submission will be peer-graded in a double-blind manner as per the criteria specified in the accompanying file, _hw5-review.xlsx_. The score thus earned will be your _Submission Score_.

Your individual score in this homework is the product of your Submission Score and Team Factor.

# Discussion

This is a lengthy and potentially confusing assignment. There is a lot to take in and it may seem complicated and daunting. So do not be shy to reach out! In case of confusion or lack of clarity, do not hesitate to contact the course staff. We also encourage you to:

- discuss with your buddy,
- post in the discussion thread linked in the Assignment module on the course page on Canvas.
