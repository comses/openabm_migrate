<?php

class OpenabmPageMigration extends DrupalNode7Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Retain old NID values
    $this->addFieldMapping('is_new')->defaultValue(TRUE);
    $this->addFieldMapping('nid', 'nid');

    $this->addFieldMapping('field_document', 'upload')
         ->sourceMigration('File');
    $this->addFieldMapping('field_document:file_class')
         ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_document:preserve_files')
         ->defaultValue(TRUE);
    $this->addFieldMapping('field_document:description', 'upload:description');
    $this->addFieldMapping('field_document:display', 'upload:display');
    $this->addFieldMapping('field_document:language')
         ->defaultValue(LANGUAGE_NONE);

    // Unmapped destination fields
    $this->addFieldMapping('field_image')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('field_view')
         ->issueGroup(t('DNM'));
  }

  // exclude pages that will conflict with existing nodes
  protected function query() {
    // Get the default query (all rows in the users table other than uid 1)
    $query = parent::query();
    // Exclude conflicting nodes
    $query->condition('nid', array(2, 33, 36, 37), 'NOT IN');
    return $query;
  }
}

class OpenabmPage2Migration extends DrupalNode7Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // These nodes will be imported with new NID values

    $this->addFieldMapping('field_document', 'upload')
         ->sourceMigration('File');
    $this->addFieldMapping('field_document:file_class')
         ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_document:preserve_files')
         ->defaultValue(TRUE);
    $this->addFieldMapping('field_document:description', 'upload:description');
    $this->addFieldMapping('field_document:display', 'upload:display');
    $this->addFieldMapping('field_document:language')
         ->defaultValue(LANGUAGE_NONE);

    // Unmapped destination fields
    $this->addFieldMapping('field_image')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('field_view')
         ->issueGroup(t('DNM'));
  }

  // import pages that would have conflicted in their old NID
  protected function query() {
    // Get the default query (all rows in the users table other than uid 1)
    $query = parent::query();
    // Include only conflicting nodes
    $query->condition('nid', array(2, 33, 36, 37), 'IN');
    return $query;
  }
}
