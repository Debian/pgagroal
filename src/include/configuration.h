/*
 * Copyright (C) 2022 Red Hat
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list
 * of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may
 * be used to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef PGAGROAL_CONFIGURATION_H
#define PGAGROAL_CONFIGURATION_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

/*
 * The main section that must be present in the `pgagroal.conf`
 * configuration file.
 */
#define PGAGROAL_MAIN_INI_SECTION "pgagroal"

/**
 * Status that pgagroal_read_configuration() could provide.
 * Use only negative values for errors, since a positive return
 * value will indicate the number of problems within sections.
 */
#define PGAGROAL_CONFIGURATION_STATUS_OK 0
#define PGAGROAL_CONFIGURATION_STATUS_FILE_NOT_FOUND -1
#define PGAGROAL_CONFIGURATION_STATUS_FILE_TOO_BIG -2
#define PGAGROAL_CONFIGURATION_STATUS_KO -3
#define PGAGROAL_CONFIGURATION_STATUS_CANNOT_DECRYPT -4

/**
 * Initialize the configuration structure
 * @param shmem The shared memory segment
 * @return 0 upon success, otherwise 1
 */
int
pgagroal_init_configuration(void* shmem);

/**
 * Read the configuration from a file
 * @param shmem The shared memory segment
 * @param filename The file name
 * @param emitWarnings true if unknown parameters have to
 *        reported on stderr
 * @return 0 (i.e, PGAGROAL_CONFIGURATION_STATUS_OK) upon success, otherwise
 *         - PGAGROAL_CONFIGURATION_STATUS_FILE_NOT_FOUND if the file does not exists
 *         - PGAGROAL_CONFIGURATION_STATUS_FILE_TOO_BIG  if the file contains too many sections
 *         - a positive value to indicate how many errors (with regard to sections) have been found
 *         - PGAGROAL_CONFIGURATION_STATUS_KO if the file has generic errors, most notably it lacks
 *           a [pgagroal] section
 */
int
pgagroal_read_configuration(void* shmem, char* filename, bool emitWarnings);

/**
 * Validate the configuration
 * @param shmem The shared memory segment
 * @param has_unix_socket Has Unix socket
 * @param has_main_sockets Has main sockets
 * @return 0 upon success, otherwise 1
 */
int
pgagroal_validate_configuration(void* shmem, bool has_unix_socket, bool has_main_sockets);

/**
 * Read the HBA configuration from a file
 * @param shmem The shared memory segment
 * @param filename The file name
 * @return 0 (i.e, PGAGROAL_CONFIGURATION_STATUS_OK) upon success, otherwise
 *         - PGAGROAL_CONFIGURATION_STATUS_FILE_NOT_FOUND if the file does not exists
 *         - PGAGROAL_CONFIGURATION_STATUS_FILE_TOO_BIG  if the file contains too many entries
 */
int
pgagroal_read_hba_configuration(void* shmem, char* filename);

/**
 * Validate the HBA configuration from a file
 * @param shmem The shared memory segment
 * @return 0 upon success, otherwise 1
 */
int
pgagroal_validate_hba_configuration(void* shmem);

/**
 * Read the LIMIT configuration from a file
 * @param shmem The shared memory segment
 * @param filename The file name
 * @return 0 (i.e, PGAGROAL_CONFIGURATION_STATUS_OK) upon success, otherwise
 *         - PGAGROAL_CONFIGURATION_STATUS_FILE_NOT_FOUND if the file does not exists
 *         - PGAGROAL_CONFIGURATION_STATUS_FILE_TOO_BIG  if the file contains too many limits
 */
int
pgagroal_read_limit_configuration(void* shmem, char* filename);

/**
 * Validate the LIMIT configuration from a file
 * @param shmem The shared memory segment
 * @return 0 upon success, otherwise 1
 */
int
pgagroal_validate_limit_configuration(void* shmem);

/**
 * Read the USERS configuration from a file
 * @param shmem The shared memory segment
 * @param filename The file name
 * @return 0 (i.e, PGAGROAL_CONFIGURATION_STATUS_OK) upon success, otherwise
 *         - PGAGROAL_CONFIGURATION_STATUS_FILE_NOT_FOUND if the file does not exists
 *         - PGAGROAL_CONFIGURATION_STATUS_FILE_TOO_BIG  if the file contains too many users
 *           (i.e., more users than the number defined in the limits)
 *         - PGAGROAL_CONFIGURATION_STATUS_KO if the file has some problem (e.g., cannot be decrypted)
 *         - PGAGROAL_CONFIGURATION_STATUS_CANNOT_DECRYPT to indicate a problem reading the content of the file

 */
int
pgagroal_read_users_configuration(void* shmem, char* filename);

/**
 * Validate the USERS configuration from a file
 * @param shmem The shared memory segment
 * @return 0 upon success, otherwise 1
 */
int
pgagroal_validate_users_configuration(void* shmem);

/**
 * Read the FRONTEND USERS configuration from a file
 * @param shmem The shared memory segment
 * @param filename The file name
 * @return 0 (i.e, PGAGROAL_CONFIGURATION_STATUS_OK) upon success, otherwise
 *         - PGAGROAL_CONFIGURATION_STATUS_FILE_NOT_FOUND if the file does not exists
 *         - PGAGROAL_CONFIGURATION_STATUS_FILE_TOO_BIG  if the file contains too many users
 *           (i.e., more users than the number defined in the limits)
 *         - PGAGROAL_CONFIGURATION_STATUS_KO if the file has some problem (e.g., cannot be decrypted)
 *         - PGAGROAL_CONFIGURATION_STATUS_CANNOT_DECRYPT to indicate a problem reading the content of the file
 */
int
pgagroal_read_frontend_users_configuration(void* shmem, char* filename);

/**
 * Validate the FRONTEND USERS configuration from a file
 * @param shmem The shared memory segment
 * @return 0 upon success, otherwise 1
 */
int
pgagroal_validate_frontend_users_configuration(void* shmem);

/**
 * Read the ADMINS configuration from a file
 * @param shmem The shared memory segment
 * @param filename The file name
 * @return 0 (i.e, PGAGROAL_CONFIGURATION_STATUS_OK) upon success, otherwise
 *         - PGAGROAL_CONFIGURATION_STATUS_FILE_NOT_FOUND if the file does not exists
 *         - PGAGROAL_CONFIGURATION_STATUS_FILE_TOO_BIG  if the file contains too many users
 *           (i.e., more users than the number defined in the limits)
 *         - PGAGROAL_CONFIGURATION_STATUS_KO if the file has some problem (e.g., cannot be decrypted)
 *         - PGAGROAL_CONFIGURATION_STATUS_CANNOT_DECRYPT to indicate a problem reading the content of the file
 */
int
pgagroal_read_admins_configuration(void* shmem, char* filename);

/**
 * Validate the ADMINS configuration from a file
 * @param shmem The shared memory segment
 * @return 0 upon success, otherwise 1
 */
int
pgagroal_validate_admins_configuration(void* shmem);

/**
 * Read the superuser from a file
 * @param shmem The shared memory segment
 * @param filename The file name
 * @return 0 (i.e, PGAGROAL_CONFIGURATION_STATUS_OK) upon success, otherwise
 *         - PGAGROAL_CONFIGURATION_STATUS_FILE_NOT_FOUND if the file does not exists
 *         - PGAGROAL_CONFIGURATION_STATUS_FILE_TOO_BIG  if the file entry is to big
 *         - PGAGROAL_CONFIGURATION_STATUS_KO if the file has some problem (e.g., cannot be decrypted)
 *         - PGAGROAL_CONFIGURATION_STATUS_CANNOT_DECRYPT to indicate a problem reading the content of the file
 */
int
pgagroal_read_superuser_configuration(void* shmem, char* filename);

/**
 * Validate the SUPERUSER configuration from a file
 * @param shmem The shared memory segment
 * @return 0 upon success, otherwise 1
 */
int
pgagroal_validate_superuser_configuration(void* shmem);

/**
 * Reload the configuration
 * @return 0 upon success, otherwise 1
 */
int
pgagroal_reload_configuration(void);

/**
 * Automatically initialize the 'pidfile'
 * if none has been specified.
 * This function is called as last step
 * from pgagroal_validate_configuration
 * because it builds the pidfile on the value
 * of unix_socket_dir.
 */
void
pgagroal_init_pidfile_if_needed(void);

/**
 * Checks if the configuration has a min set of values to
 * take into account doing a prefill. For example, there must
 * be users and limits set, otherwise it does not
 * make any sense to attempt a prefill.
 * This can be used to wrap the condituion before calling
 * other prefill functions, e.g., `pgagroal_prefill()`.
 */
bool
pgagroal_can_prefill(void);

#ifdef __cplusplus
}
#endif

#endif
