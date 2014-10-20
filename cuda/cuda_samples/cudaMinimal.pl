use strict;
use warnings;
use CUDA::Minimal;
use ExtUtils::nvcc;
use Inline C => DATA => ExtUtils::nvcc::Inline;

# Some CUDA kernels and their Perl wrappers are defined below. Let's
# create some data and invoke them!

my $N_values = 10;
my $host_data = pack('f*', 1..$N_values);

# Copy the data to the video card and get the pointer in the video card's
# memory. MallocFrom allocates enough memory and copies the contents:
my $input_dev_ptr = MallocFrom($host_data);

# Before processing the data on the video card, I need to allocate some
# memory on the card where the results will be stored. Malloc allocates
# enough memory but does not copy contents:
my $output_dev_ptr = Malloc($host_data);

# Run the kernel:
invoke_the_kernel($input_dev_ptr, $output_dev_ptr, $N_values);

# We would like to see the results, allocate an new host array:
SetSize(my $results_array, length($host_data));
# and copy the results back:
Transfer($output_dev_ptr => $results_array);
print "$_\n" foreach (unpack 'f*', $results_array);

# Finally, free the device memory:
Free($input_dev_ptr, $output_dev_ptr);

__END__

__C__

// A simple kernel that triples the value of the input data and stores
// the result in the output array:
__global__ void triple(float * in_g, float * out_g) {
    out_g[threadIdx.x] = in_g[threadIdx.x] * 3;
}

// A  little wrapper for the kernel that Inline::C knows how to parse:
void invoke_the_kernel(SV * in_SV, SV * out_SV, int N_values) {
    // Unpack the device pointers:
    float * d_in = INT2PTR(float *, SvIV(in_SV));
    float * d_out = INT2PTR(float *, SvIV(out_SV));

    // invoke the kernel:
    triple <<<1, N_values>>>(d_in, d_out);
}
