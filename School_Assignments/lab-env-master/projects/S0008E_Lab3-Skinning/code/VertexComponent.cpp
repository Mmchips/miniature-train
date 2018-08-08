//
// Created by ivoako-5 on 3/19/18.
//

#include "VertexComponent.h"

VertexComponent::VertexComponent()
{

}

VertexComponent::VertexComponent(SemanticName sn, int index, Format form)
{
    this->semName = sn;
    this->semIndx = index;
    this->format = form;
}