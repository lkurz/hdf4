C $Id$
C Interface to invoke tests for HDF Fortran interfaces.

	Program main
	implicit none
	include 'fortest.inc'

	integer nerror, retcode
	character cmd*15, test*30

C Default to cleanup *.hdf files and set verbosity to default value
	CleanUp = .TRUE.
	CleanUpCMD = 'rm -f *.hdf'
	Verbosity = VERBO_DEF

	print *, '==========================================='
	print *, 'HDF Library Fortran Interface Tests Started'
	print *, '==========================================='
	nerror = 0
	call getcmd(cmd, test, retcode)
	do while (retcode .eq. 0)
	    call runcmd(cmd, test, retcode)
	    if (retcode .ne. 0) nerror = nerror + 1
	    call getcmd(cmd, test, retcode)
	end do

	print *, '====================================='
	if (nerror .ne. 0) then
	    print*, nerror, ' Fortran test(s) failed'
	else
	    print*, 'All Fortran Interface Tests Passed'
	endif
	print *, '====================================='

	if (CleanUp) call Hsystem(CleanUpCMD)

	stop
	end


C Get a test command.
C Currently taking it from standard input.
C If EOF encounters, set retcode = 1.  Else retcode = 0.
C
	subroutine getcmd(cmd, test, retcode)
	implicit none
	include 'fortest.inc'
	
	character*(*) cmd, test
	integer retcode

	character*120 inline
	integer linelen, i

	retcode = 0

C For VMS, un-comment the next line if the asterisk
C        doesn't work
C        read(5,11,END=100,err=100) inline
	read(*,11,END=100,err=100) inline
C	print *, 'inline=', inline
	linelen = len(inline)
	i = index(inline, ' ')
	if (i .le. 0) i = linelen+1
	cmd = inline(1 : i - 1)

	do while (i .le. linelen)
	    if (inline(i:i) .eq. ' ') then
		i = i + 1
	    else
		goto 50
	    endif
	end do

50	test = inline(i:linelen)

	if (Verbosity .ge. VERBO_HI) then
	    print * , 'cmd=', cmd, ', test=', test
	endif

	retcode = 0
	return

100	retcode =1
	return
C
11	format(A120)
	end
	    

C Run the Fortran test command.
C
	subroutine runcmd(cmd, param, retcode)
	implicit none
	include 'fortest.inc'
	
	character*(*) cmd, param

	integer retcode
C
	retcode = 0

C Parse command types
C
C Verbosity level command
	if (cmd .EQ. 'Verbosity' .OR. cmd .EQ. 'verbosity') then
	    Verbosity = index('0123456789', param(1:1)) - 1
	    return
	endif
	    

C Cleanup command
C If param is Yes/No, it directs to delete the *.hdf or not.
C If param is not Yes/No, it represents the system command to delete
C    the *.hdf.  (NB: specifying system command does not imply
C    to Cleanup, i.e., it does not current CleanUp setting.
C
	if (cmd .EQ. 'Cleanup' .OR. cmd .EQ. 'cleanup') then
	    if (param .EQ. 'No' .OR. param .EQ. 'no') then
		CleanUp = .FALSE.
	    else if (param .EQ. 'Yes' .OR. param .EQ. 'yes') then
		CleanUp = .TRUE.
	    else
		CleanUpCMD = param
	    endif
	    return
	endif
	    
C	print *, '====================================='
C	print *, cmd, param
C	print *, '====================================='

C Skip command
	if (cmd .EQ. 'Skip' .OR. cmd .EQ. 'skip') then
	    call ptestban('Skipping', param)
	    return
	endif

	if (cmd .NE. 'Test' .AND. cmd .NE. 'test') then
	    print *, 'Unknown Command: ', cmd, param
	    print *, 'Try one of "Skip", "Test", "Verbosity" or "Cleanup"'
	    retcode = -1
	    return
	endif

C Test command
	if (param .EQ. 'slab') then
	    call slabwf(retcode)
	    return
	endif

	if (param .EQ. 'r24') then
	    call t24f(retcode)
	    return
	endif

	if (param .EQ. 'an') then
	    call tanf(retcode)
	    return
	endif

	if (param .EQ. 'anfile') then
	    call tanfilef(retcode)
	    return
	endif

	if (param .EQ. 'manf') then
	    call manf(retcode)
	    return
	endif

	if (param .EQ. 'mgrf') then
	    call mgrf(retcode)
	    return
	endif

	if (param .EQ. 'p') then
	    call tpf(retcode)
	    return
	endif

	if (param .EQ. 'r8') then
	    call tr8f(retcode)
	    return
	endif

	if (param .EQ. 'sdmms') then
	    call tsdmmsf(retcode)
	    return
	endif

	if (param .EQ. 'sdnmms') then
	    call tsdnmmsf(retcode)
	    return
	endif

	if (param .EQ. 'sdnnt') then
	    call tsdnntf(retcode)
	    return
	endif

	if (param .EQ. 'sdnt') then
	    call tsdntf(retcode)
	    return
	endif

	if (param .EQ. 'sdstr') then
	    call tsdstrf(retcode)
	    return
	endif

	if (param .EQ. 'vsetf') then
	    call tvsetf(retcode)
	    return
	endif

	if (param .EQ. 'stubs') then
	    call tstubsf(retcode)
	    return
	endif

C
	print *, 'Unknown Command: ', cmd, param
	retcode = -1
	return
	end

