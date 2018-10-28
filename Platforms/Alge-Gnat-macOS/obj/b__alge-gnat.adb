pragma Ada_95;
pragma Warnings (Off);
pragma Source_File_Name (ada_main, Spec_File_Name => "b__alge-gnat.ads");
pragma Source_File_Name (ada_main, Body_File_Name => "b__alge-gnat.adb");
pragma Suppress (Overflow_Check);

with System.Restrictions;
with Ada.Exceptions;

package body ada_main is

   E133 : Short_Integer; pragma Import (Ada, E133, "system__os_lib_E");
   E021 : Short_Integer; pragma Import (Ada, E021, "system__soft_links_E");
   E031 : Short_Integer; pragma Import (Ada, E031, "system__exception_table_E");
   E139 : Short_Integer; pragma Import (Ada, E139, "ada__containers_E");
   E116 : Short_Integer; pragma Import (Ada, E116, "ada__io_exceptions_E");
   E054 : Short_Integer; pragma Import (Ada, E054, "ada__strings_E");
   E056 : Short_Integer; pragma Import (Ada, E056, "ada__strings__maps_E");
   E060 : Short_Integer; pragma Import (Ada, E060, "ada__strings__maps__constants_E");
   E013 : Short_Integer; pragma Import (Ada, E013, "ada__tags_E");
   E115 : Short_Integer; pragma Import (Ada, E115, "ada__streams_E");
   E071 : Short_Integer; pragma Import (Ada, E071, "interfaces__c_E");
   E138 : Short_Integer; pragma Import (Ada, E138, "interfaces__c__strings_E");
   E033 : Short_Integer; pragma Import (Ada, E033, "system__exceptions_E");
   E136 : Short_Integer; pragma Import (Ada, E136, "system__file_control_block_E");
   E131 : Short_Integer; pragma Import (Ada, E131, "system__file_io_E");
   E118 : Short_Integer; pragma Import (Ada, E118, "system__finalization_root_E");
   E113 : Short_Integer; pragma Import (Ada, E113, "ada__finalization_E");
   E120 : Short_Integer; pragma Import (Ada, E120, "system__storage_pools_E");
   E110 : Short_Integer; pragma Import (Ada, E110, "system__finalization_masters_E");
   E108 : Short_Integer; pragma Import (Ada, E108, "system__storage_pools__subpools_E");
   E158 : Short_Integer; pragma Import (Ada, E158, "system__task_info_E");
   E069 : Short_Integer; pragma Import (Ada, E069, "system__object_reader_E");
   E049 : Short_Integer; pragma Import (Ada, E049, "system__dwarf_lines_E");
   E025 : Short_Integer; pragma Import (Ada, E025, "system__secondary_stack_E");
   E100 : Short_Integer; pragma Import (Ada, E100, "ada__strings__unbounded_E");
   E176 : Short_Integer; pragma Import (Ada, E176, "system__tasking__initialization_E");
   E044 : Short_Integer; pragma Import (Ada, E044, "system__traceback__symbolic_E");
   E200 : Short_Integer; pragma Import (Ada, E200, "ada__real_time_E");
   E129 : Short_Integer; pragma Import (Ada, E129, "ada__text_io_E");
   E184 : Short_Integer; pragma Import (Ada, E184, "system__tasking__protected_objects_E");
   E188 : Short_Integer; pragma Import (Ada, E188, "system__tasking__protected_objects__entries_E");
   E192 : Short_Integer; pragma Import (Ada, E192, "system__tasking__queuing_E");
   E198 : Short_Integer; pragma Import (Ada, E198, "system__tasking__stages_E");
   E003 : Short_Integer; pragma Import (Ada, E003, "algesdk_E");
   E002 : Short_Integer; pragma Import (Ada, E002, "adaapp_E");
   E009 : Short_Integer; pragma Import (Ada, E009, "t_E");
   E007 : Short_Integer; pragma Import (Ada, E007, "t__th_E");

   Local_Priority_Specific_Dispatching : constant String := "";
   Local_Interrupt_States : constant String := "";

   Is_Elaborated : Boolean := False;

   procedure finalize_library is
   begin
      declare
         procedure F1;
         pragma Import (Ada, F1, "algesdk__finalize_spec");
      begin
         E003 := E003 - 1;
         if E003 = 0 then
            F1;
         end if;
      end;
      E188 := E188 - 1;
      declare
         procedure F2;
         pragma Import (Ada, F2, "system__tasking__protected_objects__entries__finalize_spec");
      begin
         if E188 = 0 then
            F2;
         end if;
      end;
      E129 := E129 - 1;
      declare
         procedure F3;
         pragma Import (Ada, F3, "ada__text_io__finalize_spec");
      begin
         if E129 = 0 then
            F3;
         end if;
      end;
      E100 := E100 - 1;
      declare
         procedure F4;
         pragma Import (Ada, F4, "ada__strings__unbounded__finalize_spec");
      begin
         if E100 = 0 then
            F4;
         end if;
      end;
      declare
         procedure F5;
         pragma Import (Ada, F5, "system__file_io__finalize_body");
      begin
         E131 := E131 - 1;
         if E131 = 0 then
            F5;
         end if;
      end;
      E110 := E110 - 1;
      E108 := E108 - 1;
      declare
         procedure F6;
         pragma Import (Ada, F6, "system__storage_pools__subpools__finalize_spec");
      begin
         if E108 = 0 then
            F6;
         end if;
      end;
      declare
         procedure F7;
         pragma Import (Ada, F7, "system__finalization_masters__finalize_spec");
      begin
         if E110 = 0 then
            F7;
         end if;
      end;
      declare
         procedure Reraise_Library_Exception_If_Any;
            pragma Import (Ada, Reraise_Library_Exception_If_Any, "__gnat_reraise_library_exception_if_any");
      begin
         Reraise_Library_Exception_If_Any;
      end;
   end finalize_library;

   procedure adafinal is

      procedure Runtime_Finalize;
      pragma Import (C, Runtime_Finalize, "__gnat_runtime_finalize");

   begin
      if not Is_Elaborated then
         return;
      end if;
      Is_Elaborated := False;
      Runtime_Finalize;
      finalize_library;
   end adafinal;

   type No_Param_Proc is access procedure;

   procedure adainit is
      Main_Priority : Integer;
      pragma Import (C, Main_Priority, "__gl_main_priority");
      Time_Slice_Value : Integer;
      pragma Import (C, Time_Slice_Value, "__gl_time_slice_val");
      WC_Encoding : Character;
      pragma Import (C, WC_Encoding, "__gl_wc_encoding");
      Locking_Policy : Character;
      pragma Import (C, Locking_Policy, "__gl_locking_policy");
      Queuing_Policy : Character;
      pragma Import (C, Queuing_Policy, "__gl_queuing_policy");
      Task_Dispatching_Policy : Character;
      pragma Import (C, Task_Dispatching_Policy, "__gl_task_dispatching_policy");
      Priority_Specific_Dispatching : System.Address;
      pragma Import (C, Priority_Specific_Dispatching, "__gl_priority_specific_dispatching");
      Num_Specific_Dispatching : Integer;
      pragma Import (C, Num_Specific_Dispatching, "__gl_num_specific_dispatching");
      Main_CPU : Integer;
      pragma Import (C, Main_CPU, "__gl_main_cpu");
      Interrupt_States : System.Address;
      pragma Import (C, Interrupt_States, "__gl_interrupt_states");
      Num_Interrupt_States : Integer;
      pragma Import (C, Num_Interrupt_States, "__gl_num_interrupt_states");
      Unreserve_All_Interrupts : Integer;
      pragma Import (C, Unreserve_All_Interrupts, "__gl_unreserve_all_interrupts");
      Detect_Blocking : Integer;
      pragma Import (C, Detect_Blocking, "__gl_detect_blocking");
      Default_Stack_Size : Integer;
      pragma Import (C, Default_Stack_Size, "__gl_default_stack_size");
      Leap_Seconds_Support : Integer;
      pragma Import (C, Leap_Seconds_Support, "__gl_leap_seconds_support");
      Bind_Env_Addr : System.Address;
      pragma Import (C, Bind_Env_Addr, "__gl_bind_env_addr");

      procedure Runtime_Initialize (Install_Handler : Integer);
      pragma Import (C, Runtime_Initialize, "__gnat_runtime_initialize");

      Finalize_Library_Objects : No_Param_Proc;
      pragma Import (C, Finalize_Library_Objects, "__gnat_finalize_library_objects");
   begin
      if Is_Elaborated then
         return;
      end if;
      Is_Elaborated := True;
      Main_Priority := -1;
      Time_Slice_Value := -1;
      WC_Encoding := 'b';
      Locking_Policy := ' ';
      Queuing_Policy := ' ';
      Task_Dispatching_Policy := ' ';
      System.Restrictions.Run_Time_Restrictions :=
        (Set =>
          (False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, True, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False),
         Value => (0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
         Violated =>
          (False, False, False, True, True, False, False, False, 
           False, False, False, True, True, True, False, False, 
           True, False, False, True, True, False, True, True, 
           False, True, True, True, True, False, False, False, 
           False, False, True, False, False, True, False, True, 
           False, False, True, False, False, False, True, True, 
           False, False, True, False, False, False, False, False, 
           False, False, True, True, True, True, True, False, 
           False, True, False, True, True, True, False, True, 
           True, False, True, True, True, True, False, False, 
           True, False, False, False, False, True, True, True, 
           False, False, False),
         Count => (0, 0, 0, 0, 2, 1, 1, 0, 0, 0),
         Unknown => (False, False, False, False, False, False, False, False, False, False));
      Priority_Specific_Dispatching :=
        Local_Priority_Specific_Dispatching'Address;
      Num_Specific_Dispatching := 0;
      Main_CPU := -1;
      Interrupt_States := Local_Interrupt_States'Address;
      Num_Interrupt_States := 0;
      Unreserve_All_Interrupts := 0;
      Detect_Blocking := 0;
      Default_Stack_Size := -1;
      Leap_Seconds_Support := 0;

      Runtime_Initialize (1);

      if E021 = 0 then
         System.Soft_Links'Elab_Spec;
      end if;
      if E031 = 0 then
         System.Exception_Table'Elab_Body;
      end if;
      E031 := E031 + 1;
      if E139 = 0 then
         Ada.Containers'Elab_Spec;
      end if;
      E139 := E139 + 1;
      if E116 = 0 then
         Ada.Io_Exceptions'Elab_Spec;
      end if;
      E116 := E116 + 1;
      if E054 = 0 then
         Ada.Strings'Elab_Spec;
      end if;
      E054 := E054 + 1;
      if E056 = 0 then
         Ada.Strings.Maps'Elab_Spec;
      end if;
      if E060 = 0 then
         Ada.Strings.Maps.Constants'Elab_Spec;
      end if;
      E060 := E060 + 1;
      if E013 = 0 then
         Ada.Tags'Elab_Spec;
      end if;
      if E115 = 0 then
         Ada.Streams'Elab_Spec;
      end if;
      E115 := E115 + 1;
      if E071 = 0 then
         Interfaces.C'Elab_Spec;
      end if;
      if E138 = 0 then
         Interfaces.C.Strings'Elab_Spec;
      end if;
      if E033 = 0 then
         System.Exceptions'Elab_Spec;
      end if;
      E033 := E033 + 1;
      if E136 = 0 then
         System.File_Control_Block'Elab_Spec;
      end if;
      E136 := E136 + 1;
      if E118 = 0 then
         System.Finalization_Root'Elab_Spec;
      end if;
      E118 := E118 + 1;
      if E113 = 0 then
         Ada.Finalization'Elab_Spec;
      end if;
      E113 := E113 + 1;
      if E120 = 0 then
         System.Storage_Pools'Elab_Spec;
      end if;
      E120 := E120 + 1;
      if E110 = 0 then
         System.Finalization_Masters'Elab_Spec;
      end if;
      if E108 = 0 then
         System.Storage_Pools.Subpools'Elab_Spec;
      end if;
      if E158 = 0 then
         System.Task_Info'Elab_Spec;
      end if;
      E158 := E158 + 1;
      if E069 = 0 then
         System.Object_Reader'Elab_Spec;
      end if;
      if E049 = 0 then
         System.Dwarf_Lines'Elab_Spec;
      end if;
      E108 := E108 + 1;
      if E110 = 0 then
         System.Finalization_Masters'Elab_Body;
      end if;
      E110 := E110 + 1;
      if E131 = 0 then
         System.File_Io'Elab_Body;
      end if;
      E131 := E131 + 1;
      E138 := E138 + 1;
      E071 := E071 + 1;
      if E013 = 0 then
         Ada.Tags'Elab_Body;
      end if;
      E013 := E013 + 1;
      E056 := E056 + 1;
      if E021 = 0 then
         System.Soft_Links'Elab_Body;
      end if;
      E021 := E021 + 1;
      if E133 = 0 then
         System.Os_Lib'Elab_Body;
      end if;
      E133 := E133 + 1;
      if E025 = 0 then
         System.Secondary_Stack'Elab_Body;
      end if;
      E025 := E025 + 1;
      E049 := E049 + 1;
      E069 := E069 + 1;
      if E100 = 0 then
         Ada.Strings.Unbounded'Elab_Spec;
      end if;
      E100 := E100 + 1;
      if E044 = 0 then
         System.Traceback.Symbolic'Elab_Body;
      end if;
      E044 := E044 + 1;
      if E176 = 0 then
         System.Tasking.Initialization'Elab_Body;
      end if;
      E176 := E176 + 1;
      if E200 = 0 then
         Ada.Real_Time'Elab_Spec;
      end if;
      if E200 = 0 then
         Ada.Real_Time'Elab_Body;
      end if;
      E200 := E200 + 1;
      if E129 = 0 then
         Ada.Text_Io'Elab_Spec;
      end if;
      if E129 = 0 then
         Ada.Text_Io'Elab_Body;
      end if;
      E129 := E129 + 1;
      if E184 = 0 then
         System.Tasking.Protected_Objects'Elab_Body;
      end if;
      E184 := E184 + 1;
      if E188 = 0 then
         System.Tasking.Protected_Objects.Entries'Elab_Spec;
      end if;
      E188 := E188 + 1;
      if E192 = 0 then
         System.Tasking.Queuing'Elab_Body;
      end if;
      E192 := E192 + 1;
      if E198 = 0 then
         System.Tasking.Stages'Elab_Body;
      end if;
      E198 := E198 + 1;
      if E003 = 0 then
         Algesdk'Elab_Spec;
      end if;
      E003 := E003 + 1;
      if E002 = 0 then
         Adaapp'Elab_Body;
      end if;
      E002 := E002 + 1;
      if E007 = 0 then
         t.th'elab_spec;
      end if;
      if E007 = 0 then
         t.th'elab_body;
      end if;
      E007 := E007 + 1;
      E009 := E009 + 1;
   end adainit;

--  BEGIN Object file/option list
   --   C:\Users\Bilal\Desktop\AlgeSDK\Platforms\Alge-Gnat\obj\CMD.o
   --   C:\Users\Bilal\Desktop\AlgeSDK\Platforms\Alge-Gnat\obj\AlgeSDK.o
   --   C:\Users\Bilal\Desktop\AlgeSDK\Platforms\Alge-Gnat\obj\AdaApp.o
   --   C:\Users\Bilal\Desktop\AlgeSDK\Platforms\Alge-Gnat\obj\structdefs_h.o
   --   C:\Users\Bilal\Desktop\AlgeSDK\Platforms\Alge-Gnat\obj\t-th.o
   --   C:\Users\Bilal\Desktop\AlgeSDK\Platforms\Alge-Gnat\obj\t.o
   --   -LC:\Users\Bilal\Desktop\AlgeSDK\Platforms\Alge-Gnat\obj\
   --   -LC:\Users\Bilal\Desktop\AlgeSDK\Platforms\Alge-Gnat\obj\
   --   -LC:/gnat/2016/lib/gcc/i686-pc-mingw32/4.9.4/adalib/
   --   -static
   --   -lgnarl
   --   -lgnat
   --   -Xlinker
   --   --stack=0x200000,0x1000
   --   -mthreads
   --   -Wl,--stack=0x2000000
--  END Object file/option list   

end ada_main;
