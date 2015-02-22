SUBDIRS=plugin editor script tests

.PHONY: subdirs $(SUBDIRS)
     
subdirs: $(SUBDIRS)
     
$(SUBDIRS):
	$(MAKE) -C $@

editor: script

plugin: editor

tests: script

clean:
	-find . -name .libs -type d -exec rm -rf {} \;
	-find . -name '*.la' -exec rm -f {} \;
	-find . -name '*.lo' -exec rm -f {} \;
	-find . -name '*.o' -exec rm -f {} \;
