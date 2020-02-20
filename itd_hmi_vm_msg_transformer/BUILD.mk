##############################################################################
#
# Freescale Confidential Proprietary
#
# Copyright (c) 2016 Freescale Semiconductor;
# All Rights Reserved
#
##############################################################################
#
# THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
# INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
# IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
# THE POSSIBILITY OF SUCH DAMAGE.
#
##############################################################################

SDK_ROOT := $(call path_relative_to,$(CURDIR),$(CURR_SDK_ROOT))

ARM_APP = vm_communication

# ARM_DEFS += -fopenmp

##############################################################################
# ARM_APP
##############################################################################

ARM_APP_SRCS += app.cpp
ARM_APP_SRCS += decode.cpp
ARM_APP_SRCS += msg.pb.cc
ARM_APP_SRCS += main.cpp

##############################################################################
# include
##############################################################################
ARM_INCS += -I../include
ARM_INCS += -I$(SDK_ROOT)/include

ARM_INCS += -I$(CROSS_COMPILE_SYSROOT)/usr/include/eigen3

ARM_INCS += -I../../module/communication/tcp/include
ARM_INCS += -I../../module/communication/udp/include
ARM_INCS += -I../../module/our_thread/include
##############################################################################
# static libs
##############################################################################
ARM_APP_LIBS += ../../module/communication/tcp/$(ODIR)/libCommunicationTcp.a
ARM_APP_LIBS += ../../module/communication/udp/$(ODIR)/libCommunicationUdp.a
ARM_APP_LIBS += ../../module/our_thread/$(ODIR)/libour_thread.a
ARM_APP_LIBS += ../../module/util/$(ODIR)/libutil.a
##############################################################################
# dynamic libs
##############################################################################
# ARM_LDOPTS += -fopenmp
ARM_LDOPTS += -lpthread
ARM_LDOPTS += -lyaml-cpp
ARM_LDOPTS += -lprotobuf
