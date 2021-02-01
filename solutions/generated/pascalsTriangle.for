C
C develop.for						       Version 1.0
C	Paul Kyberd						       20 May 2020
C 
C     Version 1.0     Main routine to drive the building and display of
C                     the triangle
C
C   V1.0      Call the build function and then print it out
C
	
      program pascalsTriangle

      real	version/1.0/
      integer	flag, element

      write (6,2000) version
2000  format(' Programme to create Pascals triangle:: version  ', 
     +  F4.2)

      flag = triangleMake(8)
      if (flag .LT. 0) write(6,3000) flag
3000  format(1x,'triangle build error: return flag ',i4)

      call trianglePrint()

      element = triangleElement(5,3)
      write(6,2010) element
2010  format(1x, "element is ", i6)

      flag = triangleMake(1)
      if (flag .LT. 0) write(6,3000) flag
      call trianglePrint()

      flag = triangleMake(5)
      if (flag .LT. 0) write(6,3000) flag
      call trianglePrint()

      flag = triangleMake(0)
      if (flag .LT. 0) write(6,3000) flag
      call trianglePrint()

      end program pascalsTriangle
C
C  =======================================================================
C
      function triangleMake(rows)
C
C  Version 1.0        Paul Kyberd         10 May 2020
C  
C  V1.0          Create pascal's triangle with a given number of rows  
C
C   Call:    triangleMake(number of rows of the triangle)
C            number of rows must be greater than zero and less than 100.
C            by editting the store array the maximum size can be increased
C
C   Return:  0    success
C            -1   fail
C
C   builds a triangle in a two dimensional array - this array is then passed
C   between the functions and subroutines to allow access to the data structure
C   allow pseudo OO encapsulation in a non OO language
C
       common / pt / pRows, store(100,100)
       integer pRows, store

       integer rows
       
       write (6,2010) rows
2010   format(" number of rows is ", i4)
       pRows = rows

       if (rows .GT. 100) then
         write (6, 3000) rows
3000     format(1x, 'Number of rows ', i4, ' exceeds limits of 100')
         triangleMaker = -10
         return
      endif

C  In fortran 77 arrays are not initialised - elements contain random values
C  and need initialising modern compilers fill with zeros. Since we can't create
C  a new instance of the triangle, this is required to reset the initial conditions
C  when a second or subsequent triangle is created

      do MI=1, pRows
        do MJ = 1, pRows
          store(MI, MJ) = 0
        enddo
      enddo

C
      store(2,2) = 1 
      do MI = 3, rows+1
        nEntries = nEntries + 1
        do MJ = 2, rows+1
          store(MI, MJ) = store(MI-1, MJ-1) + store(MI-1, MJ)
        enddo
      enddo

C
      triangleMake = 0
      return 
      end function triangleMake
C
C =========================================================
C
      function triangleElement(row, column)
C
C  Version 1.0        Paul Kyberd         10 May 2020
C  
C  V1.0       Print out a particular element in terms of rows and
C             columns. Check for a legal value
C      
C   Call:    trianglePrint() - must have already called triangleMake
C
C   Return:  >0       requested element returned
C            -1       illegal value of row or column
C

      common / pt / pRows, store(100,100)
      integer pRows, store

      integer row, column

      if ((row .LE. 0) .OR. (row .GT. pRows)) then
        write (6,3000)
3000    format(1x,'Number of row illegal')
        triangleElement = -1
        return
      else if ((column .LE. pRows) .OR. (column .GT. pRows)) then
        write (6,3010)
3010    format(1x,'Number of column illegal')
        triangleElement = -1
        return
       endif

      triangleElement = store(row+1, column+1)
      return

      end function

C
C =========================================================
C
      subroutine trianglePrint()
C
C  V1.0          Print out the pascal's triangle that has been created  
C
C   Call:    trianglePrint() - must have already called triangleMake
C
C   Return:  none
C
C   prints out the "interesting part of the structure"
C   access to the data via the named common block

      common / pt / pRows, store(100,100)
      integer  pRows, store


      write (6,2000)
2000  format(1x,'Pascals triangle')

      do MI=2, pRows+1
        do MJ=2, pRows+1
          write(6,2010) store(MI, MJ)
2010      format (1x, I6, $)
          if (store(MI, MJ+1) .EQ. 0) then
            exit
          endif
        enddo
        write (6,2020)
2020    format()
      enddo

      write (6,2030)
2030  format('end')
      return
      end subroutine trianglePrint
C
C  ======================================
C  
C  Notes:
C   the print routine is to show that the triangle has been created
C   there is no way to produce the data structure required in fortran 77
C   triangleElement(row, Column) allows you to access a particular element
C   of the triangle and effectively encapsulates the data (although don't
C   let a fortran programmer use the word!) A similar function could be
C   used to return a whole row
