ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
c      written by the UFO converter
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc

C     Parameters that should not be recomputed event by event.
C     
      IF(READLHA) THEN

        G = 2 * DSQRT(AS*PI)  ! for the first init

        MDL_CONJG__CKM3X3 = 1.000000D+00

        MDL_CKM3X3 = 1.000000D+00

        MDL_CONJG__CKM1X1 = 1.000000D+00

        MDL_COMPLEXI = (0.000000D+00,1.000000D+00)

        MDL_MZ__EXP__2 = MDL_MZ**2

        MDL_MZ__EXP__4 = MDL_MZ**4

        MDL_SQRT__2 = SQRT(2.000000D+00)

        MDL_MH__EXP__2 = MDL_MH**2

        MDL_AEW = 1.000000D+00/AEWM1

        MDL_MW = SQRT(MDL_MZ__EXP__2/2.000000D+00+SQRT(MDL_MZ__EXP__4
     $   /4.000000D+00-(MDL_AEW*PI*MDL_MZ__EXP__2)/(MDL_GF*MDL_SQRT__2
     $   )))

        MDL_SQRT__AEW = SQRT(MDL_AEW)

        MDL_EE = 2.000000D+00*MDL_SQRT__AEW*SQRT(PI)

        MDL_MW__EXP__2 = MDL_MW**2

        MDL_SW2 = 1.000000D+00-MDL_MW__EXP__2/MDL_MZ__EXP__2

        MDL_CW = SQRT(1.000000D+00-MDL_SW2)

        MDL_SQRT__SW2 = SQRT(MDL_SW2)

        MDL_SW = MDL_SQRT__SW2

        MDL_G1 = MDL_EE/MDL_CW

        MDL_GW = MDL_EE/MDL_SW

        MDL_VEV = (2.000000D+00*MDL_MW*MDL_SW)/MDL_EE

        MDL_VEV__EXP__2 = MDL_VEV**2

        MDL_LAM = MDL_MH__EXP__2/(2.000000D+00*MDL_VEV__EXP__2)

        MDL_YT = (MDL_YMT*MDL_SQRT__2)/MDL_VEV

        MDL_YTAU = (MDL_YMTAU*MDL_SQRT__2)/MDL_VEV

        MDL_MUH = SQRT(MDL_LAM*MDL_VEV__EXP__2)

        MDL_I2X33 = MDL_YT*MDL_CONJG__CKM3X3

        MDL_I3X33 = MDL_CKM3X3*MDL_YT

        MDL_EE__EXP__2 = MDL_EE**2

        MDL_SW__EXP__2 = MDL_SW**2

        MDL_CW__EXP__2 = MDL_CW**2

      ENDIF
C     
C     Parameters that should be recomputed at an event by even basis.
C     
      AS = G**2/4/PI

      MDL_SQRT__AS = SQRT(AS)

      MDL_G__EXP__2 = G**2

C     
C     Definition of the EW coupling used in the write out of aqed
C     
      GAL(1) = 3.5449077018110318 / DSQRT(AEWM1)
      GAL(2) = 1D0

