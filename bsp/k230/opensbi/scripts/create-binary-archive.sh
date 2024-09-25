#!/bin/bash

function usage()
{
	echo "Usage:"
	echo " $0 [options]"
	echo "Options:"
	echo "     -h                       Display help or usage"
	echo "     -p <opensbi_source_path> OpenSBI source path"
	echo "     -o <output_path>         Build output path"
	echo "     -d                       Build and install documentation"
	echo "     -t                       Build only with no archive created"
	echo "     -j <num_threads>         Number of threads for Make (Default: 1)"
	echo "     -s <archive_suffix>      Archive name suffix (Default: unknown)"
	echo "     -x <riscv_xlen>          RISC-V XLENs for Build (Default: 0)"
	echo "                                 0: RV32 and RV64"
	echo "                                32: RV32 only"
	echo "                                64: RV64 only"
	exit 1;
}

# Command line options
NUM_THREADS=1
OUTPUT_PATH="$(pwd)/build"
OPENSBI_SOURCE_PATH="$(pwd)"
NEED_DOCS="no"
COMPILE_ONLY="no"
ARCHIVE_SUFFIX="unknown"
RISCV_XLEN=0

while getopts "hdtj:o:p:s:x:" o; do
	case "${o}" in
	h)
		usage
		;;
	d)
		NEED_DOCS="yes"
		;;
	t)
		COMPILE_ONLY="yes"
		;;
	j)
		NUM_THREADS=${OPTARG}
		;;
	o)
		OUTPUT_PATH=${OPTARG}
		;;
	p)
		OPENSBI_SOURCE_PATH=${OPTARG}
		;;
	s)
		ARCHIVE_SUFFIX=${OPTARG}
		;;
	x)
		RISCV_XLEN=${OPTARG}
		;;
	*)
		usage
		;;
	esac
done
shift $((OPTIND-1))

if [ -z "${OPENSBI_SOURCE_PATH}" ]; then
	echo "Must specify OpenSBI source path"
	usage
fi

if [ ! -d "${OPENSBI_SOURCE_PATH}" ]; then
	echo "OpenSBI source path does not exist"
	usage
fi

if [ -z "${ARCHIVE_SUFFIX}" ]; then
	echo "Archive suffice cannot be empty"
	usage
fi

build_opensbi() {
	# Setup parameters
	BUILD_NUM_THREADS=$1
	BUILD_OUTPUT_PATH=$2
	BUILD_OPENSBI_SOURCE_PATH=$3
	BUILD_DOCS=$4
	BUILD_ONLY=$5
	BUILD_RISCV_XLEN=$6
	BUILD_ARCHIVE_RISCV_XLEN=$7
	BUILD_ARCHIVE_SUFFIX=$8

	# Setup derived parameters
	BUILD_VERSION_MAJOR=$(grep "define OPENSBI_VERSION_MAJOR" "${BUILD_OPENSBI_SOURCE_PATH}/include/sbi/sbi_version.h" | sed 's/.*MAJOR.*\([0-9][0-9]*\)/\1/')
	BUILD_VERSION_MINOR=$(grep "define OPENSBI_VERSION_MINOR" "${BUILD_OPENSBI_SOURCE_PATH}/include/sbi/sbi_version.h" | sed 's/.*MINOR.*\([0-9][0-9]*\)/\1/')
	BUILD_NAME="opensbi-${BUILD_VERSION_MAJOR}.${BUILD_VERSION_MINOR}-rv${BUILD_RISCV_XLEN}"
	BUILD_ARCHIVE_NAME="opensbi-${BUILD_VERSION_MAJOR}.${BUILD_VERSION_MINOR}-rv${BUILD_ARCHIVE_RISCV_XLEN}-${BUILD_ARCHIVE_SUFFIX}"
	case "${BUILD_RISCV_XLEN}" in
	32)
		# Setup 32-bit platform list
		BUILD_PLATFORM_SUBDIR=("sifive/fu540")
		BUILD_PLATFORM_SUBDIR+=("generic")
		;;
	64)
		# Setup 64-bit platform list
		BUILD_PLATFORM_SUBDIR=("sifive/fu540")
		BUILD_PLATFORM_SUBDIR+=("nuclei/ux600")
		BUILD_PLATFORM_SUBDIR+=("kendryte/k210")
		BUILD_PLATFORM_SUBDIR+=("fpga/ariane")
		BUILD_PLATFORM_SUBDIR+=("fpga/openpiton")
		BUILD_PLATFORM_SUBDIR+=("andes/ae350")
		BUILD_PLATFORM_SUBDIR+=("generic")
		;;
	*)
		echo "Invalid Build RISC-V XLEN"
		usage
		;;
	esac

	# Ensure output directory is present
	mkdir -p "${BUILD_OUTPUT_PATH}/${BUILD_NAME}"

	# Build and install generic library
	echo "Build and install generic library XLEN=${BUILD_RISCV_XLEN}"
	echo ""
	make -C "${BUILD_OPENSBI_SOURCE_PATH}" O="${BUILD_OUTPUT_PATH}/${BUILD_NAME}" I="${BUILD_OUTPUT_PATH}/${BUILD_ARCHIVE_NAME}" PLATFORM_RISCV_XLEN="${BUILD_RISCV_XLEN}" install_libsbi install_libsbiutils -j "${BUILD_NUM_THREADS}"
	echo ""

	# Build and install relevant platforms
	for INDEX in $(seq 0 1 "$(expr ${#BUILD_PLATFORM_SUBDIR[*]} - 1)")
	do
		echo "Build and install PLATFORM=${BUILD_PLATFORM_SUBDIR[${INDEX}]} XLEN=${BUILD_RISCV_XLEN}"
		echo ""
		make -C "${BUILD_OPENSBI_SOURCE_PATH}" O="${BUILD_OUTPUT_PATH}/${BUILD_NAME}" I="${BUILD_OUTPUT_PATH}/${BUILD_ARCHIVE_NAME}" PLATFORM="${BUILD_PLATFORM_SUBDIR[${INDEX}]}" PLATFORM_RISCV_XLEN="${BUILD_RISCV_XLEN}" install_libplatsbi install_firmwares -j "${BUILD_NUM_THREADS}"
		echo ""
	done

	# Build and install docs
	if [ "${BUILD_DOCS}" == "yes" ]; then
		echo "Build and install docs"
		echo ""
		make -C "${BUILD_OPENSBI_SOURCE_PATH}" O="${BUILD_OUTPUT_PATH}/${BUILD_NAME}" I="${BUILD_OUTPUT_PATH}/${BUILD_ARCHIVE_NAME}" install_docs
		echo ""
	fi

	# Create archive file
	if [ "${BUILD_ONLY}" == "no" ]; then
		echo "Create archive ${BUILD_ARCHIVE_NAME}.tar.xz"
		echo ""
		tar  -C "${BUILD_OUTPUT_PATH}" -cJvf "${BUILD_OUTPUT_PATH}/${BUILD_ARCHIVE_NAME}.tar.xz" "${BUILD_ARCHIVE_NAME}"
		echo ""
	fi
}

case "${RISCV_XLEN}" in
0)
	build_opensbi ${NUM_THREADS} ${OUTPUT_PATH} ${OPENSBI_SOURCE_PATH} "no" "yes" "32" "" ${ARCHIVE_SUFFIX}
	build_opensbi ${NUM_THREADS} ${OUTPUT_PATH} ${OPENSBI_SOURCE_PATH} ${NEED_DOCS} ${COMPILE_ONLY} "64" "" ${ARCHIVE_SUFFIX}
	;;
32)
	build_opensbi ${NUM_THREADS} ${OUTPUT_PATH} ${OPENSBI_SOURCE_PATH} ${NEED_DOCS} ${COMPILE_ONLY} "32" "32" ${ARCHIVE_SUFFIX}
	;;
64)
	build_opensbi ${NUM_THREADS} ${OUTPUT_PATH} ${OPENSBI_SOURCE_PATH} ${NEED_DOCS} ${COMPILE_ONLY} "64" "64" ${ARCHIVE_SUFFIX}
	;;
*)
	echo "Invalid RISC-V XLEN"
	usage
	;;
esac
