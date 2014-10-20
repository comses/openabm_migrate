<?php

class OpenabmBiblioNodeMigration extends DrupalNode7Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Retain old NID values
    $this->addFieldMapping('is_new')->defaultValue(TRUE);
    $this->addFieldMapping('nid', 'nid');

    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title_field:language', 'language');

    $this->addFieldMapping('field_keywords', 'taxonomy_vocabulary_6')
         ->sourceMigration('KeywordsVocabulary')
         ->arguments(array('source_type' => 'tid'));

    $this->addFieldMapping('field_document', 'upload')
         ->sourceMigration('File');
    $this->addFieldMapping('field_document:file_class')
         ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_document:description', 'upload:description');
    $this->addFieldMapping('field_document:display', 'upload:display');
    $this->addFieldMapping('field_document:language')
         ->defaultValue(LANGUAGE_NONE);

    /* TODO: figure out how to map biblio custom fields. The are stored in biblio custom tables,
     *       so it may be a simple matter of transferring these rows during prepare().
     */
  }
}

