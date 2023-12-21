with Ada.Text_IO; use Ada.Text_IO;

procedure Main is

   type WorkArrayType is array (1..100) of Integer;

   WorkArray: WorkArrayType := (1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100);
   WorkLen: Integer := 100;

   task type Simple_Task(Index: Integer);

   task body Simple_Task is
   begin
      Put_Line("Index: "& Integer'Image(Index) & "; Value by Index: "& Integer'Image (WorkArray(Index))&"; value by index mirror: "& Integer'Image (WorkArray (WorkLen - Index)));
      WorkArray(Index) := WorkArray(Index) + WorkArray (WorkLen - Index + 1);
   end Simple_Task;


begin
   declare
      type Simple_Task_ptr is access Simple_Task;
      Task_Ptr: Simple_Task_ptr;
   begin
      while WorkLen > 1 loop
         for I in 1 .. WorkLen/2 loop
            Task_Ptr := new Simple_Task (Index => I);
         end loop;

         delay 0.01;

         WorkLen := WorkLen / 2 + WorkLen mod 2;
      end loop;
   end;

   for I of WorkArray loop
      Put(Integer'Image (I) & " , ");
   end loop;


end Main;