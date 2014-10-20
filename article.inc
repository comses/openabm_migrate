<?php

class OpenabmArticleMigration extends DrupalNode7Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Flag nodes to retain old nids
    $this->addFieldMapping('is_new')->defaultValue(TRUE);
    $this->addFieldMapping('nid', 'nid');

    $this->addFieldMapping('field_image', 'upload')
         ->sourceMigration('File');
    $this->addFieldMapping('field_image:file_class')
         ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_image:preserve_files')
         ->defaultValue(TRUE);
    $this->addFieldMapping('field_image:description', 'upload:description');
    $this->addFieldMapping('field_image:display', 'upload:display');
    $this->addFieldMapping('field_image:language')
         ->defaultValue(LANGUAGE_NONE);

    // Unmapped destination fields
    $this->addFieldMapping('field_article_type')
         ->issueGroup(t('DNM'));
  }

  // exclude pages that will conflict with existing nodes
  protected function query() {
    // Get the default query (all rows in the users table other than uid 1)
    $query = parent::query();
    // Exclude conflicting nodes
    $query->condition('nid', array(34), 'NOT IN');
    return $query;
  }
}

class OpenabmArticle2Migration extends DrupalNode7Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_image', 'upload')
         ->sourceMigration('File');
    $this->addFieldMapping('field_image:file_class')
         ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_image:preserve_files')
         ->defaultValue(TRUE);
    $this->addFieldMapping('field_image:description', 'upload:description');
    $this->addFieldMapping('field_image:display', 'upload:display');
    $this->addFieldMapping('field_image:language')
         ->defaultValue(LANGUAGE_NONE);

    // Unmapped destination fields
    $this->addFieldMapping('field_article_type')
         ->issueGroup(t('DNM'));
  }

  // import pages that would have conflicted in their old NID
  protected function query() {
    // Get the default query (all rows in the users table other than uid 1)
    $query = parent::query();
    // Include only conflicting nodes
    $query->condition('nid', array(34), 'IN');
    return $query;
  }
}
