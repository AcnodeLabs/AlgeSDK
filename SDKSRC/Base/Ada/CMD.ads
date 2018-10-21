with Interfaces.C; use Interfaces.C;

package CMD is

   MSG  : int := 16#3002#;
   VOID  : int := 16#3003#;
   ERR  : int := 16#3000#;
   SNDSET  : int := 16#3040#;
   SNDSET0  : int := 16#3040#;
   SNDSET1  : int := 16#3041#;
   SNDSET2  : int := 16#3042#;
   SNDSET3  : int := 16#3043#;
   SNDPLAY  : int := 16#3050#;
   SNDPLAY0  : int := 16#3050#;
   SNDPLAY1  : int := 16#3051#;
   SNDPLAY2  : int := 16#3052#;
   SNDPLAY3  : int := 16#3053#;
   TEXSET0  : int := 16#3230#;
   TEXSET1  : int := 16#3231#;
   TEXSET2  : int := 16#3232#;
   TEXSET3  : int := 16#3233#;
   TEXID  : int := 16#3205#;
   SNDLOOP  : int := 16#3055#;
   VIDSET  : int := 16#3007#;
   VIDPLAY  : int := 16#3008#;
   DONE  : int := 16#3101#;
   PAUSE  : int := 16#3333#;
   UNPAUSE  : int := 16#3334#;
   BEGIN_CMD  : int := 16#1111#;
   END_CMD  : int := 16#ffff#;
   TOUCH_START  : int := 16#3300#;
   TOUCH_END  : int := 16#3301#;
   TOUCHMOVE  : int := 16#3321#;
   TOUCH_START2  : int := 16#3400#;
   TOUCH_END2  : int := 16#3401#;
   TOUCHMOVE2  : int := 16#3421#;
   SCREENSIZE  : int := 16#3303#;
   TITLE  : int := 16#3013#;
   SPAWN  : int := 16#3012#;
   YOUTUBE_SHOW  : int := 16#3875#;
   YOUTUBE_CLOSE  : int := 16#3877#;
   YOUTUBE_READY  : int := 16#3876#;
   ALLSET  : int := 16#3993#;
   KEYDOWN  : int := 16#7998#;
   KEYUP  : int := 16#7999#;
   TOAST  : int := 16#3022#;
   COMMANDLINE  : int := 16#8765#;

end CMD;
