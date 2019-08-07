with Interfaces.C; use Interfaces.C;
with cmd; use cmd;
with Ada.Strings.Unbounded;
with Interfaces.C.Strings; use Interfaces.C.Strings;
with AlgeSDK; use AlgeSDK;
with HitTestCode; use HitTestCode;
with Ada.Containers; use Ada.Containers;
with Ada.Containers.Vectors;
with Text_IO; use Text_IO;
with Ada.Numerics.Float_Random;
with CAnimator; use CAnimator;
with CTimed; use CTimed;
with Stars; use Stars;

package AdaApp is

   timeVar : C_float := 0.0;
   width : Standard.Integer := 0;
   height: Standard.Integer := 0;
   can : CAnimator.CAnim;

   MIN_ALLOWABLE_DISTANCE : C_float := -1.5;
   MIN_ALLOWABLE_SPEED : C_float := 3.0;
   NORMAL_SPEED : C_float := 10.0;

   procedure Init;
   procedure Update(dt : C_float);
   procedure Render;
   procedure ProcessInput (command: Int; i1: Int; i2: Int);
   procedure DeInit;

   pragma export (CPP, Render, "AppRender");
   pragma export (CPP, Init, "AppInit");
   pragma export (CPP, Update, "AppUpdate");
   pragma export (CPP, DeInit, "AppDeInit");
   pragma export (CPP, ProcessInput, "AppProcessInput");

   -- App Specific

   ANIMSEQ_CROSSING: constant Integer	:= 1;
   ANIMSEQ_NEARING: constant Integer	:= 2;
   ANIMSEQ_SPHERE: constant Integer	:= 3;
   ANIMSEQ_SURFACE: constant Integer	:= 4;
   ANIMSEQ_LAND: constant Integer	:= 5;
   ANIMSEQ_SLINGSHOT: constant Integer	:= 6;

   keyframe : Integer := 1;
   eye,eyerot,tgt,up : f3;
   
   procedure renderStars;
   procedure onHit(hitId: Integer);
   animstep : Float := 0.0;
   animStepTimed : CTimed.CTimedT;
   deltaT : Float;
   bz : C_float := 1.0;
   nseq : Integer := 0;

end AdaApp;

