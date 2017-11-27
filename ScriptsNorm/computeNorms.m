clear all

# Argument list
arg_list = argv ();
filename1 = arg_list{1};
filename2 = arg_list{2};
level = arg_list{3};
dim = arg_list{4};
ec = "&";
# Convert strings
L = str2num(level);
D = str2num(dim);

# Number of cells in each direction
N = 2^L;

# Load data
f = load(filename1);
g = load(filename2);

# Allocate matrices
n = 1;
# Three dimensions
if (D == 3)
	for i=1:N
		for j=1:N
			for k=1:N
				rhoF(k,j,i) = f(n,4);
				rhoC(i,j,k) = g(n,4);
				n = n+1;
			end
		end
	end
# Two dimensions
else
	for i=1:N
		for j=1:N
			rhoF(i,j) = f(n,4);
			rhoC(j,i) = g(n,4);
			n = n+1;
		end
	end
endif

#imagesc(rhoF)
#figure
#imagesc(rhoC)
# Check the size
size(rhoF)
size(rhoC)

#L-Infinity norm
sub = abs(rhoF - rhoC);

b1=max(max(max(sub)))

#L1 Norm
a = 0;
h = 0;
for iy=1:N
	for ix=1:N
		a = a + abs(rhoF(ix,iy)- rhoC(ix,iy));
		h = h + (rhoF(ix,iy)- rhoC(ix,iy))*(rhoF(ix,iy)- rhoC(ix,iy));
	end
end

if (D == 3)
	h1 = sqrt(h/(N*N*N))
	d1 = a/(N*N*N)
else
	h1 = sqrt(h/(N*N))
	d1 = a/(N*N)
endif

# Allocate matrices
n = 1;
# Three dimensions
if (D == 3)
	for i=1:N
		for j=1:N
			for k=1:N
				rhoF(k,j,i) = f(n,5);
				rhoC(i,j,k) = g(n,5);
				n = n+1;
			end
		end
	end
# Two dimensions
else
	for i=1:N
		for j=1:N
			rhoF(i,j) = f(n,5);
			rhoC(j,i) = g(n,5);
			n = n+1;
		end
	end
endif

# Check the size
size(rhoF)
size(rhoC)

#L-Infinity norm
sub = abs(rhoF - rhoC);

b2=max(max(max(sub)))

#L1 Norm
a = 0;
h = 0;
for iy=1:N
	for ix=1:N
		a = a + abs(rhoF(ix,iy)- rhoC(ix,iy));
		h = h + (rhoF(ix,iy)- rhoC(ix,iy))*(rhoF(ix,iy)- rhoC(ix,iy));
	end
end

if (D == 3)
	h2 = sqrt(h/(N*N*N))
	d2 = a/(N*N*N)
else
	h2 = sqrt(h/(N*N))
	d2 = a/(N*N)
endif

# Allocate matrices
n = 1;
# Three dimensions
if (D == 3)
	for i=1:N
		for j=1:N
			for k=1:N
				rhoF(k,j,i) = f(n,6);
				rhoC(i,j,k) = g(n,6);
				n = n+1;
			end
		end
	end
# Two dimensions
else
	for i=1:N
		for j=1:N
			rhoF(i,j) = f(n,6);
			rhoC(j,i) = g(n,6);
			n = n+1;
		end
	end
endif

# Check the size
size(rhoF)
size(rhoC)

#L-Infinity norm
sub = abs(rhoF - rhoC);

b3=max(max(max(sub)))

#L1 Norm
a = 0;
h = 0;
for iy=1:N
	for ix=1:N
		a = a + abs(rhoF(ix,iy)- rhoC(ix,iy));
		h = h + (rhoF(ix,iy)- rhoC(ix,iy))*(rhoF(ix,iy)- rhoC(ix,iy));
	end
end

if (D == 3)
	h3 = sqrt(h/(N*N*N))
	d3 = a/(N*N*N)
else
	h3 = sqrt(h/(N*N))
	d3 = a/(N*N)
endif

# Allocate matrices
n = 1;
# Three dimensions
if (D == 3)
	for i=1:N
		for j=1:N
			for k=1:N
				rhoF(k,j,i) = f(n,7);
				rhoC(i,j,k) = g(n,7);
				n = n+1;
			end
		end
	end
# Two dimensions
else
	for i=1:N
		for j=1:N
			rhoF(i,j) = f(n,7);
			rhoC(j,i) = g(n,7);
			n = n+1;
		end
	end
endif

# Check the size
size(rhoF)
size(rhoC)

#L-Infinity norm
sub = abs(rhoF - rhoC);

b4=max(max(max(sub)))

#L1 Norm
a = 0;
h = 0;
for iy=1:N
	for ix=1:N
		a = a + abs(rhoF(ix,iy)- rhoC(ix,iy));
		h = h + (rhoF(ix,iy)- rhoC(ix,iy))*(rhoF(ix,iy)- rhoC(ix,iy));
	end
end

if (D == 3)
	h4 = sqrt(h/(N*N*N))
	d4 = a/(N*N*N)
else
	h4 = sqrt(h/(N*N))
	d4 = a/(N*N)
endif

# Allocate matrices
n = 1;
# Three dimensions
if (D == 3)
	for i=1:N
		for j=1:N
			for k=1:N
				rhoF(k,j,i) = f(n,8);
				rhoC(i,j,k) = g(n,8);
				n = n+1;
			end
		end
	end
# Two dimensions
else
	for i=1:N
		for j=1:N
			rhoF(i,j) = f(n,8);
			rhoC(j,i) = g(n,8);
			n = n+1;
		end
	end
endif

# Check the size
size(rhoF)
size(rhoC)

#L-Infinity norm
sub = abs(rhoF - rhoC);

b5=max(max(max(sub)))

#L1 Norm
a = 0;
h = 0;
for iy=1:N
	for ix=1:N
		a = a + abs(rhoF(ix,iy)- rhoC(ix,iy));
		h = h + (rhoF(ix,iy)- rhoC(ix,iy))*(rhoF(ix,iy)- rhoC(ix,iy));
	end
end

if (D == 3)
	h5 = sqrt(h/(N*N*N))
	d5 = a/(N*N*N)
else
	h5 = sqrt(h/(N*N))
	d5 = a/(N*N)
endif

# Allocate matrices
n = 1;
# Three dimensions
if (D == 3)
	for i=1:N
		for j=1:N
			for k=1:N
				rhoF(k,j,i) = f(n,9);
				rhoC(i,j,k) = g(n,9);
				n = n+1;
			end
		end
	end
# Two dimensions
else
	for i=1:N
		for j=1:N
			rhoF(i,j) = f(n,9);
			rhoC(j,i) = g(n,9);
			n = n+1;
		end
	end
endif

# Check the size
size(rhoF)
size(rhoC)

#L-Infinity norm
sub = abs(rhoF - rhoC);

b6=max(max(max(sub)))

#L1 Norm
a = 0;
h = 0;
for iy=1:N
	for ix=1:N
		a = a + abs(rhoF(ix,iy)- rhoC(ix,iy));
		h = h + (rhoF(ix,iy)- rhoC(ix,iy))*(rhoF(ix,iy)- rhoC(ix,iy));
	end
end

if (D == 3)
	h6 = sqrt(h/(N*N*N))
	d6 = a/(N*N*N)
else
	h6 = sqrt(h/(N*N))
	d6 = a/(N*N)
endif


# Allocate matrices
n = 1;
# Three dimensions
if (D == 3)
	for i=1:N
		for j=1:N
			for k=1:N
				rhoF(k,j,i) = f(n,10);
				rhoC(i,j,k) = g(n,10);
				n = n+1;
			end
		end
	end
# Two dimensions
else
	for i=1:N
		for j=1:N
			rhoF(i,j) = f(n,10);
			rhoC(j,i) = g(n,10);
			n = n+1;
		end
	end
endif

# Check the size
size(rhoF)
size(rhoC)

#L-Infinity norm
sub = abs(rhoF - rhoC);

b7=max(max(max(sub)))

#L1 Norm
a = 0;
h = 0;
for iy=1:N
	for ix=1:N
		a = a + abs(rhoF(ix,iy)- rhoC(ix,iy));
		h = h + (rhoF(ix,iy)- rhoC(ix,iy))*(rhoF(ix,iy)- rhoC(ix,iy));
	end
end

if (D == 3)
	h7 = sqrt(h/(N*N*N))
	d7 = a/(N*N*N)
else
	h7 = sqrt(h/(N*N))
	d7 = a/(N*N)
endif

# Allocate matrices
n = 1;
# Three dimensions
if (D == 3)
	for i=1:N
		for j=1:N
			for k=1:N
				rhoF(k,j,i) = f(n,11);
				rhoC(i,j,k) = g(n,11);
				n = n+1;
			end
		end
	end
# Two dimensions
else
	for i=1:N
		for j=1:N
			rhoF(i,j) = f(n,11);
			rhoC(j,i) = g(n,11);
			n = n+1;
		end
	end
endif

# Check the size
size(rhoF)
size(rhoC)

#L-Infinity norm
sub = abs(rhoF - rhoC);

b8=max(max(max(sub)))

#L1 Norm
a = 0;
h = 0;
for iy=1:N
	for ix=1:N
		a = a + abs(rhoF(ix,iy)- rhoC(ix,iy));
		h = h + (rhoF(ix,iy)- rhoC(ix,iy))*(rhoF(ix,iy)- rhoC(ix,iy));
	end
end

if (D == 3)
	h8 = sqrt(h/(N*N*N))
	d8 = a/(N*N*N)
else
	h8 = sqrt(h/(N*N))
	d8 = a/(N*N)
endif


aux= [d1 h1 b1;d2 h2 b2; d3 h3 b3; d4 h4 b4; d5 h5 b5; d6 h6 b6; d7 h7 b7; d8 h8 b8]
save -text norms.txt aux

