
BUILD=build
NODE_GYP=node-gyp
CONFIG=configure
MODULES=toy
ROOT=$(shell pwd)
SOURCE=source

clean:
	rm -rf $(BUILD)/*

$(MODULES): 
	cd $(CONFIG)/$@ &&\
	$(NODE_GYP) configure &&\
	cd build &&\
	make &&\
	test ! -e $(ROOT)/$(BUILD)/$@ && mkdir $(ROOT)/$(BUILD)/$@ || : &&\
	mv Release/$@.node $(ROOT)/$(BUILD)/$@/ &&\
	cp $(ROOT)/$(SOURCE)/$@/test.js $(ROOT)/$(BUILD)/$@/

.PHONY: clean  
