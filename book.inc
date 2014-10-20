<?php

class OpenabmBookMigration extends DrupalNode7Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Retain legacy node nids
    $this->addFieldMapping('is_new')->defaultValue(TRUE);
    $this->addFieldMapping('nid', 'nid');

    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title_field:language', 'language');

    $this->addFieldMapping('field_bookshelf', 'taxonomy_vocabulary_5')
         ->sourceMigration('BookshelfVocabulary')
         ->arguments(array('source_type' => 'tid'));
    $this->addFieldMapping('field_document', 'upload')
         ->sourceMigration('File');
    $this->addFieldMapping('field_document:file_class')
         ->defaultValue('MigrateFileFid');
    #$this->addFieldMapping('field_document:preserve_files')
    #     ->defaultValue(TRUE);
    $this->addFieldMapping('field_document:description', 'upload:description');
    $this->addFieldMapping('field_document:display', 'upload:display');
    $this->addFieldMapping('field_document:language')
         ->defaultValue(LANGUAGE_NONE);

    // Unmapped destination fields
    $this->addFieldMapping('field_image')
         ->issueGroup(t('DNM'));
  }

  /* TODO: the following functions to migrate the book hierarchy data do not work correctly.
   *       We need to figure out this functionality so the hierarchy is structured correctly.
   *       As this code was adapted from a D6 example, a D6 vs D7 structural difference may
   *       be the cause.
   */


  /**
   * Override parent::query to add more data to the source, in our case,
   * book hierarchy stuff.
   */
  public function query() {
    $query = parent::query();
    // Add in book parent child relationships.
    $query->join('book', 'b', 'n.nid = b.nid');
    $query->addField('b', 'bid', 'book_id');
    $query->join('menu_links', 'ml', 'b.mlid = ml.mlid');
    $query->addField('ml', 'weight', 'book_weight');
    return $query;
  }

  /**
   * Acts right after a book node has been saved. Map the book hierarchy.
   *
   * @param object $node
   *   A node object for the newly migrated book.
   * @param stdClass $row
   *   An object representing data from the source row.
   */
  public function complete($node, stdClass $row) {
    // If this is a top-level book, don't set a parent.
    $book_id = $row->nid == $row->book_id ? $node->nid : $this->lookupMigratedBook($row->book_id);
    // Book id - effectively, parent nid.
    $node->book['bid'] = $book_id;
    $node->book['nid'] = $node->nid;
    $node->book['weight'] = $row->book_weight;
    _book_update_outline($node);
    node_save($node);
  }

  /**
   * Returns a mapping for a migrated book.
   *
   * @param int $source_book_nid
   *   Nid of book in source database to lookup.
   */
  protected function lookupMigratedBook($source_book_nid) {
    $dest_book_nid = parent::handleSourceMigration('NodeBook', $source_book_nid); /* TODO: remap for the ClassMaterials type */
    return $dest_book_nid;
  }
}
