<?php

class OpenabmModelNodeMigration extends DrupalNode7Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // retain legacy node ids
    $this->addFieldMapping('is_new')->defaultValue(TRUE);
    $this->addFieldMapping('nid', 'nid');

    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title_field:language', 'language');

    $this->addFieldMapping('field_model_uri', 'field_model_uri');
    $this->addFieldMapping('field_keywords', 'taxonomy_vocabulary_6')
         ->sourceMigration('KeywordsVocabulary')
         ->arguments(array('source_type' => 'tid'));

    $this->addFieldMapping('field_model_handle', 'field_model_handle');
    $this->addFieldMapping('field_model_publication', 'field_model_publication_text');
    $this->addFieldMapping('field_model_replicated', 'field_model_replicated');
    $this->addFieldMapping('field_model_reference', 'field_model_reference');

    $this->addFieldMapping('field_model_image', 'field_model_image')
         ->sourceMigration('File');
    $this->addFieldMapping('field_model_image:file_class')
         ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_model_image:language')
         ->defaultValue(LANGUAGE_NONE);

    $this->addFieldMapping('field_model_video', 'field_model_video')
         ->sourceMigration('File');
    $this->addFieldMapping('field_model_video:file_class')
         ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_model_video:language')
         ->defaultValue(LANGUAGE_NONE);

    /* TODO: Figure out how to merge in software info and file uploads from the latest version node
     *       associated with a given model node. (Maybe a subquery extension will work.
     */
  }
}


class OpenabmModelVersionNodeMigration extends DrupalNode7Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // retain legacy node ids
    $this->addFieldMapping('is_new')->defaultValue(TRUE);
    $this->addFieldMapping('nid', 'nid');

    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title_field:language', 'language');

    $this->addFieldMapping('field_modelversion_number', 'field_modelversion_number');
    $this->addFieldMapping('field_modelversion_model', 'field_modelversion_model');
    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('field_rating', 'field_rating');

    /* TODO: for now, migrate these fields into Model Version node, but a better solution is
     *       to figure out how to merge these fields into the Model node migration.
     */
    $this->addFieldMapping('field_model_instructions', 'field_modelversion_runconditions');
    $this->addFieldMapping('field_model_platform_i', 'field_modelversion_platform');
    $this->addFieldMapping('field_model_platform_other', 'field_modelversion_platform_oth');
    $this->addFieldMapping('field_model_platform_version', 'field_modelversion_platform_ver');
    $this->addFieldMapping('field_model_language_i', 'field_modelversion_language');
    $this->addFieldMapping('field_model_language_other', 'field_modelversion_language_oth');
    $this->addFieldMapping('field_model_language_version', 'field_modelversion_language_ver');
    $this->addFieldMapping('field_model_os_i', 'field_modelversion_os');
    $this->addFieldMapping('field_model_os_other', 'field_modelversion_os_oth');
    $this->addFieldMapping('field_model_os_version', 'field_modelversion_os_version');
    $this->addFieldMapping('field_model_license_i', 'field_modelversion_license');

    $this->addFieldMapping('field_model_code', 'field_modelversion_code')
         ->sourceMigration('File');
    $this->addFieldMapping('field_model_code:file_class')
         ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_model_code:display', 'field_modelversion_code:display');
    $this->addFieldMapping('field_model_code:language')
         ->defaultValue(LANGUAGE_NONE);

    $this->addFieldMapping('field_model_documentation', 'field_modelversion_documentation')
         ->sourceMigration('File');
    $this->addFieldMapping('field_model_documentation:file_class')
         ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_model_documentation:display', 'field_modelversion_documentation:display');
    $this->addFieldMapping('field_model_documentation:language')
         ->defaultValue(LANGUAGE_NONE);

    $this->addFieldMapping('field_model_dataset', 'field_modelversion_dataset')
         ->sourceMigration('File');
    $this->addFieldMapping('field_model_dataset:file_class')
         ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_model_dataset:display', 'field_modelversion_dataset:display');
    $this->addFieldMapping('field_model_dataset:language')
         ->defaultValue(LANGUAGE_NONE);

    $this->addFieldMapping('field_model_sensitivity', 'field_modelversion_sensitivity')
         ->sourceMigration('File');
    $this->addFieldMapping('field_model_sensitivity:file_class')
         ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_model_sensitivity:display', 'field_modelversion_sensitivity:display');
    $this->addFieldMapping('field_model_sensitivity:language')
         ->defaultValue(LANGUAGE_NONE);

    $this->addFieldMapping('field_model_additional', 'field_modelversion_addfiles')
         ->sourceMigration('File');
    $this->addFieldMapping('field_model_additional:file_class')
         ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_model_additional:display', 'field_modelversion_addfiles:display');
    $this->addFieldMapping('field_model_additional:language')
         ->defaultValue(LANGUAGE_NONE);
  }

}

