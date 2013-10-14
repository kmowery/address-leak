#include "jssec.h"
#include <cxxabi.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "llvm/Support/SourceMgr.h"
#include "llvm/LLVMContext.h"
#include "llvm/DebugInfo.h"
#include "llvm/Module.h"
#include "llvm/Support/IRReader.h"


using namespace llvm;

void error(const char *format, ...);


int main(int argc, char **argv)
{
	if(argc < 2)
		error("Missing file name.");

	LLVMContext context;
	SMDiagnostic diag;
	OwningPtr<Module> module;
	
	module.reset(ParseIRFile(argv[1], diag, context));
	if(!module.get())
		error("Failed to load IR.");

	for(Module::iterator iter = module->begin(); iter != module->end(); iter++) {
		Function *func = iter;

		char *name = (char *)malloc(1024);
		size_t len = 1024;
		int err;

		name = abi::__cxa_demangle(func->getName().data(), name, &len, &err);
		if(err)
			continue;

		name[strlen(name)-2] = '\0';

		for(Function::iterator iter = func->begin(); iter != func->end(); iter++) {
			BasicBlock *block = iter;

			for(BasicBlock::iterator iter = block->begin(); iter != block->end(); iter++) {
				Instruction *inst = iter;

				if(inst->getOpcode() != Instruction::PtrToInt)
					continue;

				DILocation loc(inst->getMetadata("dbg"));

				printf("%s:%u\n", loc.getFilename().data(), loc.getLineNumber());
			}
		}
		free(name);
	}

	return 0;
}


void error(const char *format, ...)
{
	va_list args;

	va_start(args, format);
	fprintf(stderr, "Fatal error: ");
	vfprintf(stderr, format, args);
	fprintf(stderr, "\n");
	va_end(args);

	exit(1);
}
