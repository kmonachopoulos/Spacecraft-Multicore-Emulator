In European Space Agency (ESA), spacecraft simulations are systematically used targeting the education of the personnel that is responsible not only for monitoring the spacecraft during the flight; but also for studying and verificating specific telecommands packet that intended in maneuvers of the spacecraft. Operational simulation is also used for controlling the software that implemented on the central computer of the spacecraft and in general for deeply knowledge of the behavior in different specific conditions and situations. Particularly important requirement represents simulation’s high fidelity; which is achieved by including an emulator component; responsible for the execution of the actual program (OBSW: On Board Software); identical to that performed in the spacecraft model during the flight. 
Thesis goal is to investigate the construction of a latest technology emulator aiming the replacement of this; which is applied at the present time in space ESA missions. At the beginning of the construction of the emulator called “Sparcv8_Emulator”; always based in Official Sparc Architecture Version 8 Manual; and using techniques like Direct Interpretation; we accomplished to construct a machine that manages to emulate the functionality and processing the major component of the spacecraft. Considerable target of this code deals with the use of multi-processing techniques and parallel execution; so that the system can possible take advantage of multicore computers using the host operating system and therefore be able to achieve the best overall performance in terms of execution speed. In starter level; avoiding complexity; it has chosen to implement the emulator using two parallel procedures based on threads of the native operating system. 
The programming language which was used for the structure of the emulator was ANSI C; due to the primary requirement which is the speed of calculations. The specific language being low level in general, presents more benefits for the specific purpose. As a result; we succeeded to fabricate the first version of this emulator with encouraging results. The construction of emulator’s base version that we describe in the present paper, consists of about 10.000 lines of C-code developed using CodeBlocks IDE.

Test Program Overview :

In order to execute the sample program, after the initialization (by executing the "INITIALIZE" command) of the Emulator you can execute the "LOAD PROGRAM MEAN VALUE" command. This way the Emulator will be initialized as well as the Program Memory and the Data Memory with the necessary data. Later, you can run the Sample Program by executing "FREERUN", or "STEP" command. If you want to supervise the Emulator's status you can "HALT" the emulator and print the required information (Registers, Memory e.t.c).

Sample Program : 

=== List of values in data memory === 

LD 0x00000000,11
LD 0x00000004,22
LD 0x00000008,33
LD 0x0000000C,3

=== List of values in program memory ===

LD G[1],ΜΕΜ_DATA[0]     /* hex-> 0xC2002000 */
ADD O[0],G[1],G[0]      /* hex-> 0x90000001 */
LD G[1], ΜΕΜ_DATA[4]    /* hex-> 0xC2002004 */
ADD O[1],G[1],G[0]      /* hex-> 0x92000001 */
LD G[1], ΜΕΜ_DATA[8]    /* hex-> 0xC2002008 */
ADD O[2],G[1],G[0]      /* hex-> 0x94000001 */
SAVE O[2],G[1],G[0]     /* hex-> 0x95E00000 */
ADD L[0],I[0],I[1]      /* hex-> 0xA0060019 */
ADD O[0],I[2],L[0]      /* hex-> 0x90068010 */
SAVE O[2],G[0],G[0]     /* hex-> 0x95E00000 */
LD G[1], ΜΕΜ_DATA[12]   /* hex-> 0xC200200C */
UDIV I[0],I[O],G[1]     /* hex-> 0xB0760001 */
RESTORE G[1],G[0],G[0]  /* hex-> 0x83E80000 */
ADD I[0],O[0],G[0]      /* hex-> 0xB0020000 */
RESTORE G[1],G[0],G[0]  /* hex-> 0x83E80008 */
