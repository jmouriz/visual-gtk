SUBDIRS=phonebook tuner viewer editor

.PHONY: subdirs $(SUBDIRS)
     
subdirs: $(SUBDIRS)
     
$(SUBDIRS):
	@echo [Subdir] $@
	@$(MAKE) -C $@

clean:
	@echo [Cleaning]
	@for dir in $(SUBDIRS); do $(MAKE) -C $$dir clean; done
