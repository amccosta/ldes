##
# /***********************************************************************
# * Adaptive Simulated Annealing (ASA)
# * Lester Ingber <ingber@ingber.com>
# * Copyright (c) 1993-1998 Lester Ingber.  All Rights Reserved.
# * The LICENSE file must be included with ASA code.
# ***********************************************************************/
#
## $Id: Makefile,v 16.16 1998/03/06 13:48:58 ingber Exp ingber $

## ********************************************************************
## Please first read ASA-README, then examine this Makefile and NOTES.
## ********************************************************************

MANIFEST = \
	ASA \
	ASA/ASA-README \
	ASA/CHANGES \
	ASA/Makefile \
	ASA/NOTES \
	ASA/LICENSE \
	ASA/ASA-README.ps \
	ASA/ASA-README.html \
	ASA/readme.ms \
	ASA/test_asa \
	ASA/test_usr \
	ASA/user.c \
	ASA/user.h \
	ASA/user_cst.h \
	ASA/asa.c \
	ASA/asa.h \
	ASA/asa_user.h \
	ASA/asa_opt \
	ASA/ASA-README+.uu

###
###		USER OPTIONS
### The policy is to try to have the asa module (not necessarily
### the user module) compile without "errors" (not necessarily without
### "warnings").  Some additional modifications may be needed on your
### machine; e.g., you might have to comment out the `#include <stdlib.h>'
### line in asa_user.h.  See the current NOTES file for any updates on
### some standard implementations.

###
## Defaults for various options are given below.  These can be
## overridden using DEFINE_OPTIONS.  If you include several options,
## separate them by a white space or place them conveniently on several
## lines; if the latter, be sure each line to be continued ends in a "\"
## (backslash).

#DEFINE_OPTIONS = -DASA_TEST=TRUE # -DMY_TEMPLATE=TRUE

## This will run the ASA problem.
#DEFINE_OPTIONS = -DASA_TEST=TRUE
##
## This ASA_TEMPLATE will number the ASA_OUT file according to the
## system pid.  See user.h or possible changes you may have to make in the
## include file and the prototype for getpid(), as well as for the set of
## DEFINE_OPTIONS this example turns on.  (You might also have to change
## the int declaration of pid_int in user.c as well.)
#DEFINE_OPTIONS = -DASA_TEMPLATE_ASA_OUT_PID=FALSE
##
## This ASA_TEMPLATE will run the ASA test problem multiple times, and
## separate the runs into different files.  See asa_user.h for the set
## of DEFINE_OPTIONS this example turns on.
#DEFINE_OPTIONS = -DASA_TEMPLATE_MULTIPLE=FALSE
##
## This ASA_TEMPLATE illustrates the use of SELF_OPTIMIZE=TRUE.  See
## asa_user.h for the set of DEFINE_OPTIONS this example turns on.
#DEFINE_OPTIONS = -DASA_TEMPLATE_SELFOPT=FALSE
##
## This will run the ASA_SAMPLE problem.  See asa_user.h for the set of
## DEFINE_OPTIONS this example turns on.
#DEFINE_OPTIONS = -DASA_TEMPLATE_SAMPLE=FALSE
##
## This will run the ASA_QUEUE problem.  See asa_user.h for the set of
## DEFINE_OPTIONS this example turns on.
#DEFINE_OPTIONS = -DASA_TEMPLATE_QUEUE=FALSE
##
##This will run the ASA_PARALLEL code.  See asa_user.h for the set of
## DEFINE_OPTIONS this example turns on.
#DEFINE_OPTIONS = -DASA_TEMPLATE_PARALLEL=FALSE
##
## These will run the ASA_SAVE problem.  See asa_user.h for the set of
## DEFINE_OPTIONS this example turns on.
#DEFINE_OPTIONS = -DASA_TEMPLATE_SAVE=FALSE
##

###
###		Pre-Compile Options
###
## You can elect to read in the Program Options from asa_opt by
## setting OPTIONS_FILE=TRUE.  OPTIONS_FILE=TRUE can be set here or
## in asa_user.h.
#-DOPTIONS_FILE=TRUE

## If OPTIONS_FILE is set to TRUE, then also setting OPTIONS_FILE_DATA
## to TRUE will read in most initialization data from asa_opt.
#-DOPTIONS_FILE_DATA=TRUE

## You can elect to read in the Program Options from asa_opt by setting
## RECUR_OPTIONS_FILE=TRUE.  RECUR_OPTIONS_FILE=TRUE can be set here or in
## asa_user.h.
#-DRECUR_OPTIONS_FILE=FALSE

## If RECUR_OPTIONS_FILE is set to TRUE, then also setting
## RECUR_OPTIONS_FILE_DATA to TRUE will read in most initialization data
## from asa_opt.
#-DRECUR_OPTIONS_FILE_DATA=FALSE

## If COST_FILE is set to TRUE, then your own file for the cost
## function can be read into user.c.
#-DCOST_FILE=TRUE

## Setting ASA_LIB=TRUE will facilitate your running asa() as a library
## call from another program, calling asa_main() in user.c.  In the
## templates, provided, all initializations and cost function definitions
## are set up in user.c.
#-DASA_LIB=FALSE

## If ASA_TEMPLATE_LIB=TRUE, then asa_main() returns information to an
## example main() in user.c.  This illustrates how you provide the
## appropriate memory in your main().
#-DASA_TEMPLATE_LIB=FALSE

## If you do _not_ have an ANSI compiler set this to FALSE.
## If you use HAVE_ANSI=FALSE, change CC and CDEBUGFLAGS below.
#-DHAVE_ANSI=TRUE

## Most newer operating systems do not like any other I/O prototyping
## other than those in their own include files.  Other machines, like a
## Dec\-3100 under Ultrix complain that the ANSI I/O prototypes were
## inconsistent.  A Sun under 4.1.x gcc gave warnings if no I/O prototypes
## were present.  The defaults in asa_user.h use newer system prototypes.
## IO_PROTOTYPES=TRUE will uncomment out declarations for such items as
## fprintf, fflush, fclose, exit, and fscanf.
#-DIO_PROTOTYPES=FALSE

## Some systems do not have the time include files used here; others
## have different scales for time.  Setting TIME_CALC=TRUE will permit
## use of the time routines.
#-DTIME_CALC=FALSE
 
## Some systems, e.g., hpux, use other Unix-standard macros to access
## time.  Setting TIME_STD=TRUE when using TIME_CALC=TRUE will use these
## time routines instead.
#-DTIME_STD=FALSE

## Some smaller systems choke on `long int' and this option can be
## set to INT_LONG=FALSE to turn off warnings and possibly some errors.
#-DINT_LONG=TRUE

## Some machine may not permit the dimension of calloc be anything
## but int; in this case define INT_ALLOC=TRUE.  The default of FALSE
## is to set the dimension to that of LONG_INT, determined by INT_LONG.
#-DINT_ALLOC=FALSE

## You can define SMALL_FLOAT to better correlate to your own machine's
## maximum precision here if you know it.
#-DSMALL_FLOAT=1.0E-18

## You can define your own machine's minimum positive doubles here
## if you know it.

#-DMIN_DOUBLE=SMALL_FLOAT

## You can define your own machine's maximum doubles here if you
## know it.
#-DMAX_DOUBLE=1.0/SMALL_FLOAT

## You can define your own machine's maximum precision here if you
## know it.
#-DEPS_DOUBLE=SMALL_FLOAT

## When CHECK_EXPONENT is TRUE, EXPONENT_CHECK(x) in asa() checks that
## an exponent x is within a valid range and, if not, adjusts its
## magnitude to fit in the range.
#-DCHECK_EXPONENT=FALSE

## When parameter temperatures are less than SMALL_FLOAT, do not exit,
## and set them to SMALL_FLOAT.
#-DNO_PARAM_TEMP_TEST=FALSE

## When the cost temperature is less than SMALL_FLOAT, do not exit,
## and set it to SMALL_FLOAT.
#-DNO_COST_TEMP_TEST=FALSE

## You can try to use asa to self-optimize its own Program Options
## be setting SELF_OPTIMIZE=TRUE.  This can be very CPU-expensive as
## well as being dependent on your definition of recur_cost_function.
#-DSELF_OPTIMIZE=FALSE

## To use the ASA test problem, set ASA_TEST to TRUE.
#-DASA_TEST=FALSE

## To use the enhanced ASA test problem, set ASA_TEST_POINT to TRUE.
#-DASA_TEST_POINT=FALSE

## Setting USER_INITIAL_COST_TEMP to TRUE permits you to specify the
## initial cost temperature.  This can be useful in problems where you
## want to start the search at a specific scale.
#-DUSER_INITIAL_COST_TEMP=FALSE

## Different rates of parameter annealing can be set with
## RATIO_TEMPERATURE_SCALES set to TRUE.
#-DRATIO_TEMPERATURE_SCALES=FALSE

## Setting USER_INITIAL_PARAMETERS_TEMPS to TRUE permits you to specify
## the initial parameter temperatures.  This can be useful in constrained
## problems, where greater efficiency can be achieved in focussing the
## search than might be permitted just by setting upper and lower bounds.
#-DUSER_INITIAL_PARAMETERS_TEMPS=FALSE

## Different increments, used during reannealing to set each
## parameter's numerical derivatives, can be set with DELTA_PARAMETERS set
## to TRUE.
#-DDELTA_PARAMETERS=FALSE

## QUENCH_PARAMETERS permits you to alter the basic algorithm to
## perform selective "quenching," i.e., faster temperature cooling than
## permitted by the ASA algorithm.  This can be very useful, e.g., to
## quench the system down to some region of interest, and then to perform
## proper annealing for the rest of the run.
#-DQUENCH_PARAMETERS=FALSE

## If QUENCH_COST is set to TRUE, the scale of the power of the
## temperature schedule used for the acceptance function can be altered in
## a similar fashion to that described above when QUENCH_PARAMETERS is set
## to TRUE.
#-DQUENCH_COST=FALSE

## When QUENCH_PARAMETERS is TRUE, if QUENCH_PARAMETERS_SCALE is TRUE,
## then the temperature scales and the temperature indexes are affected by
## User_Quench_Param_Scale[].  When QUENCH_PARAMETERS is TRUE, if
## QUENCH_PARAMETERS_SCALE is FALSE, only the temperature indexes are
## affected by User_Quench_Param_Scale[].
#-DQUENCH_PARAMETERS_SCALE=TRUE

## When QUENCH_COST is TRUE, if QUENCH_COST_SCALE is TRUE, then the
## temperature scale and the temperature index are affected by
## User_Quench_Cost_Scale[0].  When QUENCH_COST is TRUE, if
## QUENCH_COST_SCALE is FALSE, only the temperature index is affected by
## User_Quench_Cost_Scale[0].
#-DQUENCH_COST_SCALE=TRUE

## To use testing templates in the user.c and asa.c files, associated
## with several OPTIONS, set ASA_TEMPLATE to TRUE.
#-DASA_TEMPLATE=FALSE

## It can be useful to return additional information to the user
## module from the asa module.  When OPTIONAL_DATA is set to TRUE, an
## additional pointer, *Asa_Data,  is available in DEFINES *OPTIONS to
## gather such data.
#-DOPTIONAL_DATA=FALSE

## It can be useful to return additional integer information to the
## user module from the asa module.  When OPTIONAL_DATA_INT is set to
## TRUE, an additional pointer, *Asa_Data_Int,  is available in DEFINES
## *OPTIONS to gather such data.
#-DOPTIONAL_DATA_INT=FALSE

## The function used for the cost_function temperature  schedule is of
## the form test_temperature in asa.c.  You can define your own function
## of test_temperature adaptively in user.c in user_cost_schedule() (and
## in recur_user_cost_schedule() if SELF_OPTIMIZE is TRUE) by setting
## USER_COST_SCHEDULE to TRUE.
#-DUSER_COST_SCHEDULE=FALSE

## The standard Boltzmann probability distribution is used for the
## acceptance test.  You can adaptively change this using Asymp_Exp_Param
## by setting USER_ACCEPT_ASYMP_EXP to TRUE.
#-DUSER_ACCEPT_ASYMP_EXP=FALSE

## The standard Boltzmann probability distribution is used for the
## acceptance test.  You can adaptively change this with your own function
## in user.c in user_acceptance_test() (and in
## recur_user_acceptance_test() if SELF_OPTIMIZE is TRUE) by setting
## USER_ACCEPTANCE_TEST to TRUE.
#-DUSER_ACCEPTANCE_TEST=FALSE

## The ASA generating probability distribution us used to generate new
## states.  You can adaptively change this with your own function in
## user.c in user_generating_distrib() (and in
## recur_user_generating_distrib() if SELF_OPTIMIZE is TRUE) by setting
## USER_GENERATING_FUNCTION to TRUE.
#-DUSER_GENERATING_FUNCTION=FALSE

## If you wish to adaptively control the algorithm controlling
## reannealing of the cost function, this can be done in user.c in
## user_reanneal_cost() (and in recur_user_reanneal_cost() if
## SELF_OPTIMIZE is TRUE) by setting USER_REANNEAL_COST to TRUE.
#-DUSER_REANNEAL_COST=FALSE

## The macro used for reannealing parameter temperatures
## #define FUNCTION_REANNEAL_PARAMS(temperature, tangent, max_tangent) \
##  (temperature * (max_tangent / tangent))
## is defined in asa.h.  If you wish to adaptively control this function
## it can be defined in user.c in user_reanneal_params() (and in
## recur_user_reanneal_params() if SELF_OPTIMIZE is TRUE) by setting
## USER_REANNEAL_PARAMETERS to TRUE.
#-DUSER_REANNEAL_PARAMETERS=FALSE

## MAXIMUM_REANNEAL_INDEX is the maximum index (number of steps) at
## which the initial temperature and the index of the temperature are
## rescaled to avoid losing machine precision.
#-DMAXIMUM_REANNEAL_INDEX=50000

## REANNEAL_SCALE is the reannealing scale used when
## MAXIMUM_REANNEAL_INDEX is exceeded.
#-DREANNEAL_SCALE=10

## When ASA_SAMPLE is set to TRUE, data is collected by asa to
## importance-sample the users' variable space.
#-DASA_SAMPLE=FALSE

## When ASA_QUEUE is set to TRUE, a FIFO queue saves generated states,
## to avoid extra cost function calculations.
#-DASA_QUEUE=FALSE

## When ASA_RESOLUTION is set to TRUE, Coarse_Resolution[] defines the
## resolution of parameters in the fit.
#-DASA_RESOLUTION=FALSE

## When FITLOC is set to TRUE, three subroutines become available to
## shunt asa() over to a local simplex optimization.
#-DFITLOC=FALSE

## If FITLOC is set to TRUE and FITLOC_ROUND is TRUE, then each time
## parameters are passed to or between the local routines, they are first
## processed by rounding integers or respecting rounding according to
## ASA_RESOLUTION constraints.
#-DFITLOC_ROUND=TRUE

## When FITLOC is set to TRUE and FITLOC_PRINT is TRUE, the local
## fitting routines print out from the user module.
#-DFITLOC_PRINT=TRUE

## When ASA_PARALLEL is set to TRUE, ASA is run in parallel-processor
## mode.
#-DASA_PARALLEL=FALSE

## When ASA_SAVE is set to TRUE, asa saves enough information after
## each newly accepted state to restart from that point.
#-DASA_SAVE=FALSE

## When SYSTEM_CALL is set to FALSE, asa avoids a system calls, e.g.,
## as in asa.c when ASA_SAVE is set to TRUE, to copy asa_save to
## asa_save.old.  This is useful on machines that do not permit these
## commands.
#-DSYSTEM_CALL=TRUE

## When FDLIBM_POW is set to TRUE, a user-defined function s_pow() is
## used instead of pow().  This may be desirable on some machines when a
## speed-up can be realized.
#-DFDLIBM_POW=FALSE

## When FDLIBM_LOG is set to TRUE, a user-defined function s_log() is
## used instead of log().  This may be desirable on some machines when a
## speed-up can be realized.
#-DFDLIBM_LOG=FALSE

## When FDLIBM_EXP is set to TRUE, a user-defined function s_exp() is
## used instead of exp().  This may be desirable on some machines when a
## speed-up can be realized.
#-DFDLIBM_EXP=FALSE

###
###		Printing Options
###
## Setting ASA_PRINT to FALSE will suppress all printing within asa.
#-DASA_PRINT=TRUE

## The name of the output file containing all printing from asa If you
## wish to attach a process number use ASA_OUT=\"asa_out_$$$$\" If
## ASA_OUT=\"STDOUT\" then ASA will print to stdout.
#-DASA_OUT=\"asa_out\"

## If your wish to have the printing from asa be sent to a file
## determined dynamically from the user module, set USER_ASA_OUT to
## TRUE, and define the Program Option *Asa_Out_File in the user module.
## (This overrides any ASA_OUT settings.)  In user.c, if
## USER_OPTIONS->Asa_Out_File = "STDOUT";, then ASA will print to stdout.
#-DUSER_ASA_OUT=FALSE

## Setting ASA_PRINT_INTERMED to FALSE will suppress intermediate
## printing within asa.
#-DASA_PRINT_INTERMED=TRUE

## Setting ASA_PRINT_MORE to TRUE will print out more intermediate
## information, e.g., new parameters whenever a new minimum is reported.
#-DASA_PRINT_MORE=FALSE

## The field width and precision for doubles is specified as
## G_FIELD.G_PRECISION.
#-DG_FIELD=12
#-DG_PRECISION=7

DEFINE_OPTIONS = -DASA_TEST=FALSE -DQUENCH_PARAMETERS=TRUE -DQUENCH_COST=TRUE -DTIME_CALC=TRUE

###
###		Compiler Choices
###
## If HAVE_ANSI=TRUE use this block; otherwise, use the K&R block below.
## The gnu C compiler is the default.
#CC = g++
CC = gcc
#CDEBUGFLAGS = -g -O -Wall # MY_TEMPLATE_flags
CDEBUGFLAGS = -O6 -s -mpentium # -DLOG # MY_TEMPLATE_flags
## If you wish to include some profile statistics
#CDEBUGFLAGS = -g -O -pg -Wall
##
## If you use your system's ANSI compiler, e.g., named cc, use this block.
## Sun's ANSI compiler is named acc, so use CC = acc for this one.

#CC = acc
#CDEBUGFLAGS = -O

## If HAVE_ANSI=FALSE use this K&R block.
#CC = cc
#CDEBUGFLAGS = -O

CFLAGS = $(CDEBUGFLAGS) $(DEFINE_OPTIONS)

all: compile
#	make compile
#	make run
#	make profile

###
###		Document Formatting
###
doc:
## Use groff if you have it; add pep or colcrt to delete extra
## formatting.  Under groff, using `more' or `less' presents an enhanced
## text.  Otherwise, standard UNIX macros are fine.
	groff -wall -R -t -Tascii -mgs readme.ms > ASA-README+
	pep ASA-README+ > ASA-README
## The next 2 lines use standard UNIX utilities
#	refer -e -P -n readme.ms | tbl | nroff -ms > ASA-README+
#	refer -e -P -n readme.ms | tbl | nroff -ms | colcrt > ASA-README
##
## Similarly, you may format your own PostScript ASA-README.ps.
##
	groff -wall -R -t -e -mgs readme.ms > ASA-README.ps
## if you format ps with Sun's NeWSprint,
#	refer -e -P -n readme.ms | tbl | eqn | troff -ms -t | \
#pl --r --e "" :opost > ASA-README.ps
## These macros construct ASA-README.html
	HTML/xread_html

###
###		Other Standard Arguments to Make
###
# MY_TEMPLATE_macros
#
USEROBJS = user.o # the name of the calling object file
ASAOBJS = asa.o # the ASA optimization object file
EXTRAOBJS = radcalcdir2.o data.o lex.yy.o y.tab.o
ASA_USER_INCL = asa.h user.h
# MY_TEMPLATE_objs
# MY_TEMPLATE_incl
# Use this 2-line compile instead of the next one if using MY_TEMPLATE_objs
#compile: $(USEROBJS) $(ASAOBJS) $(MY_TEMPLATE_objs)
#	@$(CC) $(LDFLAGS) -o asa_run $(USEROBJS) $(ASAOBJS) -lm $(MY_TEMPLATE_objs)
compile: $(USEROBJS) $(ASAOBJS) $(EXTRAOBJS)
	@$(CC) $(LDFLAGS) -o asa_run $(USEROBJS) $(ASAOBJS) $(EXTRAOBJS) -lm
## test for memory leaks
#compile: $(USEROBJS) $(ASAOBJS)
#	@$(CC) $(LDFLAGS) -o asa_run $(USEROBJS) $(ASAOBJS) /usr/local/lib/leak.o -lm

## If COST_FILE is set to FALSE, user_cst.h may be deleted.  If the
## name user_cst.h is changed, then this might be changed here as well.
$(USEROBJS): user.h user_cst.h # MY_TEMPLATE_user_incl
$(ASAOBJS): asa.h
$(ASA_USER_INCL): asa_user.h
# MY_TEMPLATE_depends

profile:
	gprof -z asa_run > asa_profile

## CC and CFLAGS are passed into main, to be recorded in user_out.
## use a low value of nice for runs that are time- and CPU-intensive.
run:
	asa_run $(CC) $(CFLAGS) # MY_TEMPLATE_run
#	nice -19 asa_run $(CC) $(CFLAGS)
#	profile

clean:
	rm -f *\.o asa_run # MY_TEMPLATE_clean core gmon.out

realclean:
	rm -f *\.o asa_run user_out* asa_out* core asa_save* asa_rcur asa_sfop \
	asa_[A-D]_[a-d] # MY_TEMPLATE_realclean gmon.out

docclean:
	rm -f ASA-README ASA-README.ps

## This shar is the comp.sources.unix/volume15/cshar version.
shar:
	( uuencode ASA-README+ ASA-README+ > ASA-README+.uu ; \
	cd .. ; shar -o ASA-shar $(MANIFEST) ; \
	cd ASA ; /bin/rm ASA-README+.uu )

## Some versions of shar require a -f instead of -o.
#	(cd .. ; shar -f ASA-shar $(MANIFEST))

tgz:
	(cd .. ; tar cBf - ASA | gzip --best > ASA.tar.gz)

