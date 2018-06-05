//
// typedef.h
//  my_Account
//
//  Created by hubao on 2018/5/28.
//  Copyright © 2018年 cltx. All rights reserved.
//

#ifndef basefunc_h
#define basefunc_h
//
//#include <cstring>
//#include <iostream>
////#include "typedef.h"
////
////char* make8Bit(char *p,uint32_t num){
////    //char *res=p;
////    char *q=p;
////    bool flag=false;
////    for (int i=2;i>=0;i--)
////    {
////        int carry=num/std::pow(10,i);
////        if (carry>0)
////        {
////            *(p++)=carry+'0';
////            flag=true;
////        }
////        else{
////            if(flag){
////                *(p++)=carry+'0';
////            }
////        }
////        num = num % (int)std::pow(10,i);
////
////    }
////    if (!flag){
////        *(p++)='0';
////    }
////    *(p++)='.';
////    return p;
////}
////
////char* changeIP(uint32_t num){
////
////    char *res=new char[16];
////    char *p=res;
////    for (int i=0;i<4;i++)
////    {
////        uint32_t tmp=(num>>((3-i)*8))&0xFF;
////        p = make8Bit(p,tmp);
////    }
////    p--;
////    *p='\0';
////    return res;
////}
//
//std::string  GetIPString(UINT aiIP){
//    std::string lstrIP = std::string("127.0.0.1");
//    return lstrIP;
//}
//
//uint32_t GetIPTYPE(char* str)
//{
//#define X    -999
//#define EN    900
//#define DT    990
//
//    static const int16_t MAP[] =
//            {
//                    EN, X, X, X, X, X, X, X, X,EN, X, X, X, X, X, X,
//                    X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
//                    EN, X, X, X, X, X, X, X, X, X, X, X, X, X,DT, X,
//                    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, X, X, X, X, X, X,
//                    X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
//                    X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
//                    X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
//                    X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
//                    X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
//                    X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
//                    X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
//                    X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
//                    X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
//                    X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
//                    X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
//                    X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X
//            };
//
//    int16_t d1, d2, d3, d4, v;
//    int8_t val[4];
//    int i;
//
//
//    for(i=0; i<4; i++) {
//        do {
//            d1 = MAP[*(str+0)];    // 1st char
//
//            d2 = MAP[*(str+1)];    // 2nd char
//            if(d2 > 9) {
//                if(i == 3)    {if(d2 != EN) return 0;}
//                else          {if(d2 != DT) return 0;}
//
//                v = d1;
//                str += 2;
//                break;
//            }
//
//            d3 = MAP[*(str+2)];    // 3rd char
//            if(d3 > 9) {
//                if(i == 3)    { if(d3 != EN) return 0;}
//                else          { if(d3 != DT) return 0;}
//
//                v = d1 * 10 + d2;
//                str += 3;
//                break;
//            }
//
//            d4 = MAP[*(str+3)];    // 4th char
//            if(d4 > 9) {
//                if(i == 3)    {if(d4 != EN) return 0;}
//                else          {if(d4 != DT) return 0;}
//
//                v = d1 * 100 + d2 * 10 + d3;
//                str += 4;
//                break;
//            }
//        } while(0);
//
//        if(v < 0 || v > 255) return 0;
//        val[i] = (char) v;
//    }
//
//    return *(uint32_t*) val;
//
//#undef X
//#undef EN
//#undef DT
//}

#endif
