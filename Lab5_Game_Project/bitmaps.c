#include "bitmaps.h"
#include <stdlib.h>
#include <stdint.h>
#define ANIM_COUNT_RESET_VAL 10
uint8_t animCount = 1;

const unsigned char grassblock[20 * 25 * 2 + 1] =
("\351\062\011\063IC\011;\310\062(CHCHKGK(C\310:\310:(C\010;\307:(CHC(C(C(C\352C\013"
 "DkT*L\351CiT\210\\\211\\\212\\KT\353C\312CkT*L\011DiT\211\\\211\\\212TjT\313"
 ";\313;\013DkL\253T\252\\\251\\\252\\kL\353C\353;\311;\351;JL\253T\312T\312"
 "\\\312\\\211L)D\014D\013D+DKL\213LJT*TkT+D\353;+DIL)LJL\213L\213LkTkTjLID\212"
 "L\252T\253TkL\012<(\063\010\063\353C\353;+<\252L\312T\253TKL\012<\012<\353;\353"
 "CJL\251T\251TiT\211;\212;\313;\312C\253K\351\062\252CjL\252TITh;i;\313;\353"
 "\063\314\063\213\063\013D\212T\213\\\353S\210\"\351*\313C\252\\+\\&\"iC\212\\"
 "\212\\\313SG*\250*\313C\353;\312\063I\063\313CMT\011LJCi*\311\062\352CiTk\\\310"
 "\062\252C\252\\*TkCI*\311*\353CjL\212TJT\312CJ;\312C\352:j*\313\062\254C+D\313"
 "S\351\062\312CkT\312;\013\063I*\251*\312CiT\251\\\212\\\311C\351*\211*J*\213"
 "\062\313\062J;\210\032I*\252:*;\212C\251*)*k\062\252**\063)L\251\\\211\\\350CH"
 "+\012*\012*\213\062\312\062\011;j\"+\062*:\212:\312:)\062\011*\213\062\313\062\013\063"
 "\013LJ\\\310K\310C\310;\011\"I*\352\062\312\062\012\063\313*\214:\311)\310)\310"
 ")\011*I*\352\062\013\063\013\063\313K\213Sg*H;jT\312\062j;\353KK;\353\062\353*\253"
 "\062j\062)\062\011*\313:k;\313C\213C\352*+;\353B(*\011\063\013LK;\013DKL\213C\213"
 "\062\313*\313*\253\062J*\010*K;\353CLL\253C\251*\313\062\212\062)*\352*\254;K;"
 "\353C\353C\012\063)*\213\062\253*\254\062j*(\"K;\313;\353;*;)*j\062k\062\011*\313"
 "\062\214;\253\062*\063\213;\312\062\351!J\062j*\314:j\062\010\"\252\062*\063\213;\352"
 ":\350)\012\062\012:\351\061J\062\313:\311)h*+;\253\062\351)\311)\011*\253:J\062\250"
 ")\310)I*+;\312:\310)\250\061\251\061\251\061\311)\351)h!\307!j\062J\062\251)\311"
 ")\351)*\062\351)\251)\210!\247!J\062J\062\310)g)G)\210)\251\061\251)&!&!\210)"
 "\250)\210)\311\061\251)\250)\210)h)'!&!\210)\311)\250)F)\006!H)i)\251\061\345"
 "(\346(\006)g)\207\061\250\061\210)&!&!\006!\345\040\345(\006)g)\207)F)\005!\006)H)\211"
 "\061\006\061\006\061\006)&)F\061g)G)\345\040\005)F\061\005\061\345\060\005\061&)F)E\061F\061&\061"
 "')G\061F\071F\071&\061\005)\005\061\005\061\006)\305\040%\061\206AE\071%\061&\061%)\005)E\071\206"
 "AF\071\006)\005)F\061E\061\005)\345(\345\060FA&\071\345(\005)%\061%\061&\061\005)\345(\344("
 "%\071FAF\071\005\061\345(%)\005)\345(\345(\345\060fAF\071\345(\004!\344(\005)&\061\345("
 "\345(\005\061&\071F\071&\071\005)\345(\345\040\345\040\345(&\061gA\005)\005)\344\040\004!\005"
 "!\345\040\345(\345(F\061\207Af\071&\061\345(\304(\305(");

const unsigned char bmp_enemy_data[23 * 23 * 2 + 1] =
("\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37"
 "\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37"
 "\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37"
 "\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37"
 "\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\16x\37\0\37"
 "\0\37\0\37\0\37\0\0\0\0\0\0\0\0\0\0\0\37\0\37\0\37\0\37\0\37\0\16x\37\0\37"
 "\0\37\0\37\0\37\0\37\0\16x\37\0\37\0\37\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
 "\0\0\37\0\37\0\37\0\16x\37\0\37\0\37\0\37\0\37\0\37\0\16x\16x\0\0\0\0\0\0"
 "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\16x\16x\37\0\37\0\37\0\37\0\37\0"
 "\37\0\37\0\37\0\0\0\0\0\0\0\0\0\0\0\367\275\367\275\367\275\0\0\0\0\0\0\0"
 "\0\0\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\0\0\0\0\0\0\0\0\367\275"
 "\367\275\367\275\0\370\367\275\367\275\367\275\0\0\0\0\0\0\0\0\37\0\37\0\37"
 "\0\37\0\37\0\37\0\37\0\37\0\0\0\0\0\0\0\367\275\0\0\0\0\0\370\0\0\0\370\0"
 "\0\0\0\367\275\0\0\0\0\0\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\0\0\0\0\0\0"
 "\367\275\0\0\0\0\0\370\0\0\0\0\0\0\0\370\0\0\0\0\367\275\0\0\0\0\0\0\37\0"
 "\37\0\37\0\37\0\37\0\37\0\0\0\0\0\0\0\0\0\367\275\0\0\0\370\0\0\0\0\0\0\0"
 "\370\0\0\367\275\0\0\0\0\0\0\0\0\37\0\37\0\37\0\37\0\37\0\37\0\0\0\0\0\377"
 "\377\0\0\0\0\367\275\0\0\0\370\0\0\0\370\0\0\367\275\0\0\0\0\377\377\0\0\0"
 "\0\37\0\37\0\37\0\37\0\37\0\37\0\0\0\0\0\0\0\377\377\0\0\0\0\367\275\0\0\0"
 "\370\0\0\367\275\0\0\0\0\377\377\0\0\0\0\0\0\37\0\37\0\37\0\37\0\37\0\37\0"
 "\0\0\0\0\0\0\0\0\377\377\0\0\0\0\367\275\367\275\367\275\0\0\0\0\377\377\0"
 "\0\0\0\0\0\0\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\0\0\0\0\0\0\377\377\377"
 "\377\0\0\0\0\0\0\0\0\0\0\377\377\377\377\0\0\0\0\0\0\37\0\37\0\37\0\37\0\37"
 "\0\37\0\37\0\37\0\0\0\0\0\0\0\0\0\377\377\377\377\0\0\0\0\0\0\377\377\377"
 "\377\0\0\0\0\0\0\0\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\0\0\0\0"
 "\0\0\0\0\0\0\377\377\377\377\377\377\0\0\0\0\0\0\0\0\0\0\37\0\37\0\37\0\37"
 "\0\37\0\37\0\37\0\37\0\16x\16x\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
 "\0\0\0\0\16x\16x\37\0\37\0\37\0\37\0\37\0\37\0\16x\37\0\37\0\37\0\0\0\0\0"
 "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\37\0\37\0\37\0\16x\37\0\37\0\37\0\37\0\37\0\37"
 "\0\16x\37\0\37\0\37\0\37\0\37\0\0\0\0\0\0\0\0\0\0\0\37\0\37\0\37\0\37\0\37"
 "\0\16x\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37"
 "\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37"
 "\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37"
 "\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37"
 "\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0\37\0");
 
 unsigned char *bmp_green_enemy_data = NULL;
 
 
unsigned char bmp_player_data[30 * 30 * 2 + 1] =
("\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037"
 "\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037"
 "\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037"
 "\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037"
 "\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037"
 "\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037"
 "\000\037\000\037\000\037\000p\371p\371p\371p\371p\371p\371p\371p\371p\371p\371\037\000\037"
 "\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000p\371\037\000\037\000\037\000\037"
 "\000\037\000p\371p\371p\371p\371p\371p\371p\371p\371p\371p\371\037\000\037\000\037\000\037"
 "\000\037\000p\371\037\000\037\000\037\000\037\000\037\000\037\000p\371\037\000\037\000\037\000\037\000p\371p"
 "\371\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377p\371"
 "p\371\037\000\037\000\037\000\037\000p\371\037\000\037\000\037\000\037\000\037\000\037\000p\371\037\000p\371"
 "\037\000\037\000p\371\377\377\016x\016x\016x\016x\016x\016x\016x\016x\377\377p\371\037\000"
 "\037\000p\371\037\000p\371\037\000\037\000\037\000\037\000\037\000\037\000p\371\037\000p\371\037\000\037"
 "\000p\371p\371p\371p\371p\371p\371p\371p\371p\371p\371p\371p\371\037\000\037\000p"
 "\371\037\000p\371\037\000\037\000\037\000\037\000\037\000\037\000p\371\037\000p\371\037\000\037\000\037\000"
 "p\371p\371p\371B\345B\345B\345B\345p\371p\371p\371\037\000\037\000\037\000p\371\037"
 "\000p\371\037\000\037\000\037\000\037\000\037\000\037\000p\371\037\000p\371\037\000\037\000\037\000p\371p"
 "\371p\371p\371p\371p\371p\371p\371p\371p\371\037\000\037\000\037\000p\371\037\000p\371"
 "\037\000\037\000\037\000\037\000\037\000\037\000p\371p\371p\371\037\000\037\000\037\000p\371p\371\340"
 "\377\340\377\340\377\340\377\340\377\340\377p\371p\371\037\000\037\000\037\000p\371"
 "p\371p\371\037\000\037\000\037\000\037\000\037\000\037\000\037\000p\371p\371\037\000\037\000\037\000\037"
 "\000p\371p\371p\371p\371p\371p\371p\371p\371\037\000\037\000\037\000\037\000p\371p\371\037"
 "\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000p\371p\371p\371\037\000\037\000p\371p"
 "\371p\371p\371p\371p\371p\371p\371\037\000\037\000p\371p\371p\371\037\000\037\000\037\000"
 "\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000p\371p\371\037\000\000\000p\371p\371p\371"
 "p\371p\371p\371p\371p\371\000\000\037\000p\371p\371\037\000\037\000\037\000\037\000\037\000\037\000"
 "\037\000\037\000\037\000\037\000\037\000\037\000\037\000p\371p\371p\371\000\000p\371p\371p\371p\371"
 "p\371p\371\000\000p\371p\371p\371\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000"
 "\037\000\037\000\037\000\037\000\037\000\037\000\037\000p\371p\371\215\377\377\377\377\377\377"
 "\377\377\377\215\377p\371p\371\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037"
 "\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000p\371p\371\377\377\377\377"
 "\377\377\377\377\377\377\377\377p\371p\371\037\000\037\000\037\000\037\000\037\000\037\000\037"
 "\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000p\371p\371p\371p\371p"
 "\371p\371p\371p\371p\371p\371p\371p\371\037\000\037\000\037\000\037\000\037\000\037\000\037\000"
 "\037\000\037\000\037\000\037\000p\371p\371p\371p\371p\371p\371p\371p\371p\371p\371p\371"
 "p\371p\371p\371p\371p\371p\371p\371p\371p\371p\371p\371\037\000\037\000\037\000\037"
 "\000\037\000\037\000\037\000\037\000p\371p\371\037\000\037\000p\371p\371\037\000\037\000p\371p\371\037"
 "\000\037\000p\371p\371\037\000\037\000p\371p\371\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037"
 "\000\037\000\037\000p\371p\371\037\000\037\000p\371p\371\037\000\037\000p\371p\371\037\000\037\000p"
 "\371p\371\037\000\037\000p\371p\371\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000"
 "\037\000p\371p\371\037\000\037\000p\371p\371\037\000\037\000p\371p\371\037\000\037\000p\371p\371"
 "\037\000\037\000p\371p\371\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000p\371"
 "p\371\037\000\037\000p\371p\371\037\000\037\000p\371p\371\037\000\037\000p\371p\371\037\000\037"
 "\000p\371p\371\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000p\371p\371\037"
 "\000\037\000p\371p\371\037\000\037\000p\371p\371\037\000\037\000p\371p\371\037\000\037\000p\371p"
 "\371\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000p\371p\371\037\000\037\000"
 "p\371p\371\037\000\037\000p\371p\371\037\000\037\000p\371p\371\037\000\037\000p\371p\371\037"
 "\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037"
 "\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037"
 "\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037"
 "\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037"
 "\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037"
 "\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000");


 void togglePlayerBitmap(){
	 if(--animCount == 0) {
     uint8_t fgcoloura = 0x70;
     uint8_t fgcolourb = 0xF9;
     uint8_t bgcoloura = 0x1F;
     uint8_t bgcolourb = 0x00; 
     uint8_t *curPixA;
     uint8_t *curPixB;
     for(uint8_t i = 19; i < 25; i++) {
         for(uint8_t j = 3*2; j < 25*2; j+=2){ 
              curPixA = &bmp_player_data[BMP_PLAYER_WIDTH*2*i + j];
              curPixB = &bmp_player_data[BMP_PLAYER_WIDTH*2*i + j + 1];

             if(*curPixA == fgcoloura && *curPixB == fgcolourb) {
                 *curPixA = bgcoloura;
                 *curPixB = bgcolourb;
             } else if(*curPixA == bgcoloura && *curPixB == bgcolourb) {
                 *curPixA = fgcoloura;
                 *curPixB = fgcolourb;
             }
             
         }
     }
		 animCount = ANIM_COUNT_RESET_VAL;
	 }
 }

 void initializeGreenEnemy() {
	 if(bmp_green_enemy_data == NULL)
			bmp_green_enemy_data = malloc(23*23*2 + 1);
	 
	 uint16_t toReplace = 0x0000;
	 uint16_t replaceWith = 0x0400;
		 
	 for(int i = 0; i < 23*23*2; i+=2) { 
		 if((bmp_enemy_data[i] == (toReplace & 0xFF)) && (bmp_enemy_data[i + 1] == (toReplace >> 8))) {
			 bmp_green_enemy_data[i] = replaceWith & 0xFF;
			 bmp_green_enemy_data[i+1] = replaceWith >> 8;
		 }
		 else {
			 bmp_green_enemy_data[i] = bmp_enemy_data[i];
			 bmp_green_enemy_data[i+1] = bmp_enemy_data[i+1];
		 }
	 }			 
		 
 }