/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "asn/nr-rrc-15.6.0.asn1"
 * 	`asn1c -fcompound-names -pdu=all -findirect-choice -fno-include-deps -gen-PER -no-gen-OER -no-gen-example -D rrc`
 */

#ifndef	_RRC_PUCCH_Config_H_
#define	_RRC_PUCCH_Config_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>
#include "RRC_PUCCH-ResourceSetId.h"
#include "RRC_PUCCH-ResourceId.h"
#include "RRC_SchedulingRequestResourceId.h"
#include <NativeInteger.h>
#include "RRC_PUCCH-SpatialRelationInfoId.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct RRC_SetupRelease_PUCCH_FormatConfig;
struct RRC_PUCCH_PowerControl;
struct RRC_PUCCH_ResourceSet;
struct RRC_PUCCH_Resource;
struct RRC_SchedulingRequestResourceConfig;
struct RRC_PUCCH_SpatialRelationInfo;

/* RRC_PUCCH-Config */
typedef struct RRC_PUCCH_Config {
	struct RRC_PUCCH_Config__resourceSetToAddModList {
		A_SEQUENCE_OF(struct RRC_PUCCH_ResourceSet) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *resourceSetToAddModList;
	struct RRC_PUCCH_Config__resourceSetToReleaseList {
		A_SEQUENCE_OF(RRC_PUCCH_ResourceSetId_t) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *resourceSetToReleaseList;
	struct RRC_PUCCH_Config__resourceToAddModList {
		A_SEQUENCE_OF(struct RRC_PUCCH_Resource) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *resourceToAddModList;
	struct RRC_PUCCH_Config__resourceToReleaseList {
		A_SEQUENCE_OF(RRC_PUCCH_ResourceId_t) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *resourceToReleaseList;
	struct RRC_SetupRelease_PUCCH_FormatConfig	*format1;	/* OPTIONAL */
	struct RRC_SetupRelease_PUCCH_FormatConfig	*format2;	/* OPTIONAL */
	struct RRC_SetupRelease_PUCCH_FormatConfig	*format3;	/* OPTIONAL */
	struct RRC_SetupRelease_PUCCH_FormatConfig	*format4;	/* OPTIONAL */
	struct RRC_PUCCH_Config__schedulingRequestResourceToAddModList {
		A_SEQUENCE_OF(struct RRC_SchedulingRequestResourceConfig) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *schedulingRequestResourceToAddModList;
	struct RRC_PUCCH_Config__schedulingRequestResourceToReleaseList {
		A_SEQUENCE_OF(RRC_SchedulingRequestResourceId_t) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *schedulingRequestResourceToReleaseList;
	struct RRC_PUCCH_Config__multi_CSI_PUCCH_ResourceList {
		A_SEQUENCE_OF(RRC_PUCCH_ResourceId_t) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *multi_CSI_PUCCH_ResourceList;
	struct RRC_PUCCH_Config__dl_DataToUL_ACK {
		A_SEQUENCE_OF(long) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *dl_DataToUL_ACK;
	struct RRC_PUCCH_Config__spatialRelationInfoToAddModList {
		A_SEQUENCE_OF(struct RRC_PUCCH_SpatialRelationInfo) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *spatialRelationInfoToAddModList;
	struct RRC_PUCCH_Config__spatialRelationInfoToReleaseList {
		A_SEQUENCE_OF(RRC_PUCCH_SpatialRelationInfoId_t) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *spatialRelationInfoToReleaseList;
	struct RRC_PUCCH_PowerControl	*pucch_PowerControl;	/* OPTIONAL */
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RRC_PUCCH_Config_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RRC_PUCCH_Config;
extern asn_SEQUENCE_specifics_t asn_SPC_RRC_PUCCH_Config_specs_1;
extern asn_TYPE_member_t asn_MBR_RRC_PUCCH_Config_1[15];

#ifdef __cplusplus
}
#endif

#endif	/* _RRC_PUCCH_Config_H_ */
#include <asn_internal.h>