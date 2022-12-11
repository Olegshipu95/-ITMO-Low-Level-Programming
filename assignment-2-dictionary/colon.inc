%define POINTER 0

%macro colon 2
	%ifid %2
		%2:		dq POINTER
		%define POINTER %2
	%else
		%error "Id should be a pointer"
	%endif
	
    %ifstr %1
		db %1, 0			
	%else
		%error "Content should be a string"
	%endif
    
	

%endmacro
