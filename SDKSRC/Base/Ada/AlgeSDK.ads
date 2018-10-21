-- now this is online at https://github.com/AcnodeLabs/xalgit.git
with Interfaces.C; use Interfaces.C;
with Interfaces.C.Strings; use Interfaces.C.Strings;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;
with Ada.Containers.Vectors; use Ada.Containers;
with CMD; use CMD;
--
 package AlgeSDK is

   FACTOR_RADIANS_DEGREES : constant Float := 57.295779513082;

   type f3 is
      record
         x,y,z : float;
      end record;

   type Position is
      record
         values : f3;
      end record;

   type Orientation is
      record
         values : f3;
      end record;

  

   type GameObject is tagged
      record
         pos : Position;
         rot  : Orientation;
         modelId : int;
         scale : float;
      end record;

--   package GameObjects is new Vectors (Natural, GameObject);
--   use GameObjects;

  procedure alPushI (cmd: Int; x: Int; y: Int);
  procedure alPushP (cmd: Int; param1: Strings.chars_ptr; param2: Strings.chars_ptr);

  procedure alBillBoardBegin;
  procedure alBillBoardEnd;
   procedure alLoadIdentity;
   procedure alPushMatrix;
   procedure alPopMatrix;
  procedure alaluLookAt(x1: C_float; y1: C_float;z1: C_float; x2: C_float; y2: C_float; z2:C_float; x: C_float; y: C_float; z:C_float);
  procedure alTriangle(size: C_float);
  procedure alLine(x1: C_float; y1: C_float; x2: C_float; y2: C_float);
  procedure alCircle(r: C_float;segments: Int);
  procedure alRect(w: C_float;h: C_float);
  procedure alLoadModel(alx: Strings.chars_ptr; tga: Strings.chars_ptr ; id: int; size: C_float);
   procedure alDrawModel (id: int);
   procedure alScaleModel(id: int; sx: C_float; sy: C_float;sz: C_float);
   procedure alAlphaTest (enable: int; fA: C_float := 0.4); -- 0=>unset ; 1=>set GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA
  function alModelBounds(id: int) return float;
  procedure alDrawModelTranslateRotate (id: int;
                                           posx: C_float := 0.0 ;posy : C_float := 0.0 ;posz :C_float := 0.0;
                                           angle: C_float := 0.0;x: C_float := 0.0 ;y: C_float := 0.0; z: C_float := 0.0;
                                           rotatefirst: int := 0; billboard: int := 0
                                       );

    procedure alTranslateRotate (
                                           posx: C_float := 0.0 ;posy : C_float := 0.0 ;posz :C_float := 0.0;
                                           angle: C_float := 0.0;x: C_float := 0.0 ;y: C_float := 0.0; z: C_float := 0.0
                                          );
  procedure alScalef (x: C_float := 0.0 ;y : C_float := 0.0 ;z :C_float := 0.0);

   pragma Import (C, alPushP, "PushP");
   pragma Import (C, alPushI, "PushI");
   pragma Import (C, alTriangle, "alTriangle");
   pragma Import (C, alLine, "alLine");
   pragma Import (C, alCircle, "alCircle");
   pragma Import (C, alRect, "alRect");

   pragma Import (C, alLoadIdentity, "alLoadIdentity");
   pragma Import (C, alBillBoardBegin, "alBillBoardBegin");
   pragma Import (C, alBillBoardEnd, "alBillBoardEnd");
   pragma Import (C, alaluLookAt, "alaluLookAt");
   pragma Import (C, alModelBounds, "alModelBounds");
   pragma Import (C, alAlphaTest, "alAlphaTest");


   pragma Import (C, alLoadModel, "alLoadModel");--
   pragma Import (C, alDrawModel, "alDrawModel");--
   pragma Import (C, alDrawModelTranslateRotate, "alDrawModelTranslateRotate");--
   pragma Import (C, alTranslateRotate, "alTranslateRotate");--
   pragma Import (C, alScaleModel, "alScaleModel");--
   pragma Import (C, alPushMatrix, "alPushMatrix");--
   pragma Import (C, alPopMatrix, "alPopMatrix");--
  pragma Import (C, alScalef, "alScalef");

  end AlgeSDK;
