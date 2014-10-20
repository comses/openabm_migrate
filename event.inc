<?php

class OpenabmEventMigration extends DrupalNode7Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Retain old NID values
    $this->addFieldMapping('is_new')->defaultValue(TRUE);
    $this->addFieldMapping('nid', 'nid');

    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title_field:language', 'language');

    $this->addFieldMapping('field_event_type')
         ->defaultValue(2); // Conference & Workshops
    $this->addFieldMapping('field_event_type:source_type')
         ->defaultValue('tid');

    /* TODO: Need to figure out how to set a default value for the OG group assignment */
    #$this->addFieldMapping('og_group_ref')
    #     ->defaultValue(t('comses'));

    $this->addFieldMapping('field_date', 'field_eventdate');
    $this->addFieldMapping('field_date:to', 'field_eventdate:value2');
    $this->addFieldMapping('field_date:rrule', 'field_eventdate:rrule');

    $this->addFieldMapping('field_submission_deadline', 'field_submissiondeadline');
    $this->addFieldMapping('field_earlyregistration', 'field_earlyregistration');
    #$this->addFieldMapping('field_location_address', 'field_location');

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
  }

  // exclude pages that will conflict with existing nodes
  protected function query() {
    // Get the default query (all rows in the users table other than uid 1)
    $query = parent::query();
    // Exclude conflicting nodes
    $query->condition('nid', array(9, 20, 21, 27, 57, 58, 61, 62, 63, 68, 69, 70, 71, 83, 84, 85, 189, 191, 193, 197, 207, 208, 221), 'NOT IN');
    return $query;
  }
}

class OpenabmEvent2Migration extends DrupalNode7Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Don't retain old NID values

    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title_field:language', 'language');

    $this->addFieldMapping('field_event_type')
         ->defaultValue(2); // Conference & Workshops
    $this->addFieldMapping('field_event_type:source_type')
         ->defaultValue('tid');

    /* TODO: Need to figure out how to set a default value for the OG group assignment */
    #$this->addFieldMapping('og_group_ref')
    #     ->defaultValue(t('comses'));

    $this->addFieldMapping('field_date', 'field_eventdate');
    $this->addFieldMapping('field_date:to', 'field_eventdate:value2');
    $this->addFieldMapping('field_date:rrule', 'field_eventdate:rrule');

    $this->addFieldMapping('field_submission_deadline', 'field_submissiondeadline');
    $this->addFieldMapping('field_earlyregistration', 'field_earlyregistration');
    #$this->addFieldMapping('field_location_address', 'field_location');

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
  }

  // only include pages that conflict with existing nodes
  protected function query() {
    // Get the default query (all rows in the users table other than uid 1)
    $query = parent::query();
    // Include conflicting nodes
    $query->condition('nid', array(9, 20, 21, 27, 57, 58, 61, 62, 63, 68, 69, 70, 71, 83, 84, 85, 189, 191, 193, 197, 207, 208, 221), 'IN');
    return $query;
  }
}
