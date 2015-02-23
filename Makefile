SUBDIRS=plugin editor script tests

.PHONY: subdirs $(SUBDIRS)
     
subdirs: $(SUBDIRS)
     
$(SUBDIRS):
	@echo [Subdir] $@
	@$(MAKE) -C $@

clean:
	@echo [Cleaning]
	@for dir in $(SUBDIRS); do $(MAKE) -C $$dir clean; done

editor: script

plugin: editor

tests: script
