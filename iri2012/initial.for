        SUBROUTINE MY_INITIAL
        COMMON/const2/icalls,nmono,iyearo,idaynro,rzino,igino,ut0
        COMMON /CONST/UMR  /const1/humr,dumr   /ARGEXP/ARGMAX

              icalls=0
              nmono=-1
              iyearo=-1
              idaynro=-1
              rzino=-1
              igino=-1
              ut0=-1
        if(icalls.lt.1) then
        	ARGMAX=88.0
        	pi=ATAN(1.0)*4.
        	UMR=pi/180.
        	humr=pi/12.
        	dumr=pi/182.5
        	ALOG2=ALOG(2.)
        	ALG10=ALOG(10.)
        	ALG100=ALOG(100.)
        	endif
        RETURN
        END
        
        