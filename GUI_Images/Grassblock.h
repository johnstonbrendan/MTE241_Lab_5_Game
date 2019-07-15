/*  GIMP header image file format (RGB): C:\Users\nielm\Documents\MTE241_Lab_5_Game\GUI_Images\Grassblock.h  */

static unsigned int width = 20;
static unsigned int height = 25;

/*  Call this macro repeatedly.  After each use, the pixel data can be extracted  */

#define HEADER_PIXEL(data,pixel) {\
pixel[0] = (((data[0] - 33) << 2) | ((data[1] - 33) >> 4)); \
pixel[1] = ((((data[1] - 33) & 0xF) << 4) | ((data[2] - 33) >> 2)); \
pixel[2] = ((((data[2] - 33) & 0x3) << 6) | ((data[3] - 33))); \
data += 4; \
}
static char *header_data =
	".FV,.W\"-1'F)0'*).VN%1':$2GF%3'B!3'E`2'2$0&N&/6N$2'6(0W&$/6M`17:!"
	"27F!2G>#2G>%2'2&1HZ82I&@5YV>4I>82HZ,69Z+7Z\"(7Z*.7:&75IJ?2XZ>1HN6"
	"5IV=3I:329\",5)V+7*.+7:.-6Z&259R608J908J>1I\":49R?5Z6<7*648*6-7J:2"
	"4IR91(^<0HR;/HB,0XZ*39F35J:;6:F67:N47*J34*\"/1):/2I&B29.?296<3)J?"
	"3J&?5)J85I>36)V92Y6=0H^>2):93)B03)6-3YJ64J&;4Z&<59^?59^=3YR529F."
	"4Z.86Z>86Z6@3IR=/Y&6-7:$.'.'2XZ>0H^=0)693Z666*F46*2<3)J;/9\"1/I\"5"
	"08V=18V=4)F66J:.6Z6/6)V/0H.+/H.3/XN=2XJ73(2@.&^01(674Y^86J>16)N/"
	"0GZ&/7Z./HN9.8Z<.(FB-8\":2)*96:.58Z\"958R:*V\"$,&V+18N@8J>87)><)E1U"
	"1WR,8:.48J&568J:+EI],&6%1HJ>/XV:.XB8-'N.1XN;6INJ4I*02'F7+ER--&N-"
	"28R85I^.7YR=-6B&2H:17*225)>627V@+%F+,&B-2(Z>4IR86Z&76)F62HB2/GB4"
	"1XB6/6R2+UZ1.&N;2H6A2I295HN=-V^-18B65)R:0XB6.7&;+5F-,F:+1(B459Z/"
	"8Z:.8:.21HJ/,6^/+F\"+,%B3-F*=.6F=07B4(F.%,UJ./V670G:52(*7,F6*+5:-"
	"-5^9,V67.7:53)608*6/7J..1(Z(,'B'+5&2+U*7.&.;.&B8/7.0)E^3-E6>/567"
	"/6&30&B6-%6.,%\".-F*:-&B=.7*=3Y\"979F63HF&1(F#0(N%*U&-,5N/.6Z3-VN4"
	".W\"5,&N=/&&B,$J+,$N&+4N%+U\"+,5N--VR2-G\"9-W&<4(F?5(*:,5QY/WB%6)Z5"
	".6J20WZ438V;0GN<.&R;,&R>.&><-5V5-52/,U\")/VN:07R92HN;1(&:,VZ30G>;"
	"1VZ<,5>(.G\"/3)&:07J92Y&:49F?1H&@-&*:,VF@,VF<-F>>,UJ1+5.$07B<18V@"
	"4)BA286;,V:/-FB9.6\"8+56+,VV508:C0'B?1(R>1(Z;.7&3+%2.-V*=,F>?-F:A"
	",5R1*5:#07F;0HN@0HR</W65,56+-UV7.UR9,%./-6F908\"F.V2:.7>6/X*=-VN4"
	"*TZ)-UB8,5V7/&BA-5V3*U\"#.662.G>80(*>/FZ7,TV(.E.1/5.4-4V.-EJ3/6F:"
	",$N++UV'0'6<.F>9+4R*+TF/,E.//&2<-EB3+D:&+DN&+5J)0'6>/FB8,DN&-T>("
	"-T:)-D:),TF*,4R+)SZ!*$A_-ER1-5B3+D>),4B/,$R--563,$V.,$6+*D\"$)D1`"
	"-5J1-5B2+TB(+CU_+CE],T\"&-$6,,D:-)S5X)S9W+4\"!,4:(,$*$-DB.+46++T6("
	"+4&$+CZ#)S5Y)S1W+T&\",4B*+D6&+#EW*C)T,#F!,S^*-42.+\"UN+\"UQ+#%U,CQ^"
	"-T!_-T6(+D\"'*39X*C1R*C-Q*RYN+RUP,#%T,#Q^,4)_+SAQ*S!M+#%V,3F\".$.+"
	".C)Q-S%Q,S)S,S5U-SAV,SQZ+CA]*2UM,#-L.3IQ-S-L-BYL-3!P,35R,3IR.#MP"
	".3ER-#1T,39Y-#I\\0#MV/#ES.#=R,S)P-C%O-#)M,3%S*RMI-S=O1D-W0#MP.C1O"
	".#5S,C1O,#)I/CMO14!X/3IW,C-R+3!O.CMU.#EO,S-L,\"YL-RYO13MT/S9V,\"YM"
	",3%K.39L.C=M-C9Q+S%N+2]L,\"YH/C5N1#MU/SEU-#)O+B]L+S1P,#)N+2YJ,\"UL"
	"-B]P1#UX0#EV+B]J*S!H+2]H,3-M-#9Q+2YK+RYK-3!K/C9Q0#IU/#=R,S%M+R]K"
	"*2UK*RUK+BUL.39V1#]`,S)N,3%K*BYG*3!H*3!J*R]K+2]K+RYJ.SAS2$-^03QW"
	".S9R,B]J+2MG+\"MI";
