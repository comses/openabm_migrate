<?php

/**
 * Update mapping for migrating OpenABM user accounts.
 */
class OpenabmUserMigration extends DrupalUser7Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Pass the old uid through
    $this->addFieldMapping('uid', 'uid');
    // Tell user_save to create a new account with the given uid (otherwise it sees the
    // uid and assumes you're updating an account).
    $this->addFieldMapping('is_new')
         ->defaultvalue(1);

    /* TODO: Figure out how to merge in the custom fields from the legacy Profile2 entity.
     */
  }
}
