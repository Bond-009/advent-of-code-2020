program day1
    implicit none

    integer :: i, j, k
    integer, dimension(200) :: input

    open(10, file='input', status='old')
    do i = 1, 200
        read(10, *) input(i)
    end do
    close(10)

    do i = 1, 200
        do j = 1, 200
            do k = 1, 200
                if (input(i) + input(j) + input(k) == 2020) then
                    print *, input(i) * input(j) * input(k)
                    stop
                end if
            end do
        end do
    end do

end program day1
