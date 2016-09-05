// http://blog.ioactive.com/2012/05/enter-dragonbook-pt-2.html


// This example is to concisely explaine the C specification attack
// I really liked this bug since it's an abuse of the "undefined operation" of a C compiler
// There is no actual flaw in the code here, if examined by a human (and those 0x7fff values obfuscated with #define's)
// there bug is injected when the compiler ignore's it's own eviropnment limits (this code should not build, but it does)
// with the right massaging there are no warnings, no way to know that there is a gaping security hole in the code (except if you do binary analysis/dissassembly) 
// 

// I call this copper since the bug manifests itself in the abuse of a struct field (Copperfield being some magic guy right;)?
typedef struct _copper
{
  char field1[0x7fffffff];
  char field2[0x7fffffff];
  char pad0;
  char pad1;
} copper, *pcopper;

int main(int argc, char **argv)
{
    copper david;

    printf("sizeof david = %x\n", sizeof(david));
    printf("sizeof david’s copper.field1 = %x\n", sizeof(david.field1));

       if(argc > 1 && strlen(argv[argc-1]) < sizeof(david.field1))
              strncpy_s(david.field1, argv[argc-1], sizeof(david.field1));

    return 0;
}
