c iripla.for
c computes electron density for plasmaspheric models
c use:  g95 -o ozh iripla.for

       	COMMON /const1/humr,dumr

        	pi=ATAN(1.0)*4.
        	UMR=pi/180.
        	humr=pi/12.
        	dumr=pi/182.5

	      print *,'L-value, magnetic latitude'
        	read(5,*) xl,xmlat
      	xne = OHZDEN(XL,XMLAT)
		print*,'L, MLAT, Ne/m-3'
		print*,xl,xmlat,xne
		stop
		end

c
       REAL FUNCTION GALLDEN(XL,IDOY,R12)
C--------------------------------------------------------------
C Plasmasphere model of Gallager et al. (2000) up to plasmapause
C   INPUT:  XL       L-value
C           IDOY     day of year
C           R12      12-months running mean of sunspot number
C   OUTPUT: GALLDEN  electron density in m-3   
C--------------------------------------------------------------
       COMMON /const1/humr,dumr
         y1=-0.79*xl + 5.3
         y2=dumr*(idoy+9)
         y5=0.15*(cos(y2)-0.5*cos(2*y2))
         y6=y5+0.00127*R12-0.0635
         y7=y6*exp(-(xl-2)/1.5)
         xlogNe=y1+y7
         if(abs(xlogNe).gt.38.0) xlogNe=sign(38.0,xlogNe)
         gallden=10**(xlogNe+6.0)
       RETURN          
       END             
C
C
      REAL FUNCTION CAADENET(XL,XMLT)
C--------------------------------------------------------------
C Plasmasphere model of Carpenter & Anderson (1992) for 
C extended plasma trough
C   INPUT:  XL       L-value
C           XMLT     magnetic local time in hours
C   OUTPUT: CAADENET  electron density in m-3   
C--------------------------------------------------------------
         y1=5800+300*xmlt
         if(xmlt.ge.6.0.and.xmlt.le.15.0) y1=-800+1400*xmlt
         y2=y1/xl**4.5
         y3=1.0-exp(-(xl-2.0)/10.0)
         caadenet=(y2+y3)*1.E6
       RETURN          
       END             
C
C
      REAL FUNCTION CAADEN(XL,IDOY,R12)
C--------------------------------------------------------------
C Plasmasphere model of Carpenter & Anderson (1992) up to 
C plasmapause
C   INPUT:  XL       L-value
C           IDOY     day of year
C           R12      12-months running mean of sunspot number
C   OUTPUT: CAADEN  electron density in m-3   
C--------------------------------------------------------------
       COMMON /const1/humr,dumr
         y1=-0.3145*xl + 3.9043
         y2=dumr*(idoy+9)
         y5=0.15*(cos(y2)-0.5*cos(2*y2))
         y6=y5+0.00127*R12-0.0635
         y7=y6*exp(-(xl-2)/1.5)
         xlogNe=y1+y7
		 if(abs(xlogNe).gt.38.0) xlogNe=sign(38.0,xlogNe)
         caaden=10**(log10Ne+6.0)
       RETURN          
       END             
C
C
      REAL FUNCTION OHZDEN(XL,XMLAT)
C--------------------------------------------------------------
C Plasmasphere model of Ozhogin et al. (2012) up to plasmapause
C   INPUT:  XL       L-value
C           XMLAT    magnetic latitude
C   OUTPUT: OHZDEN  electron density in m-3   
C--------------------------------------------------------------
       COMMON /CONST/UMR,PI
         y1=4.4693-0.4903*xl
		 if(abs(y1).gt.38.0) y1=sign(38.0,y1)
         xneq=10**y1
         xinv=acos(sqrt(1.0/xl))/umr
         y2=1.01*xmlat/xinv
         y3=cos(pi*y2/2.0)
         y4=y3**(-0.75)
         ohzden=1.0E6*xneq*y4
       RETURN          
       END             
C
C

