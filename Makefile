checkout-submodules:
	git submodule update --init --recursive

maintainer-update-submodules:
	git submodule update --recursive --remote --init
